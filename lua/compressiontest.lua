-- This program tests DICOM communication with any compression on sending and/or receiving server
-- It times c-store over the local network and read from file (still in cache) and decompression
-- Author: Marcel van Herk, 20130818

require('niftyutil')

function filesize(f)
  local h = io.open(f)
  if h==nil then 
    return 0
  else
    local s = h:seek('end', 0)
    h:close()
    return s
  end
end

receivecompression = {
  --'un', 
  'j1', 'j2', 'j3', 'j4', 'j450', 'j5', 'j6', 
  --'jk', 'jl', 'jl25', 'jl10', 'jl05',
  --'n2', 'n3', 'n4', 'k4'
  }

sendcompression = {
  'un'
  }

testimage = '0009703828:1.3.46.670589.5.2.10.2156913941.892665340.475317'
--testimage = 'c:\\t.dcm'
--testimage = 'head_mri.dcm'

count = 100

-- cleanup possible leftovers
if fileexists('compressiontest.txt') then 
  os.remove('compressiontest.txt')
end
os.execute('del /q/s testserver\\*.*')
os.execute('rmdir /q/s testserver')

-- add testserver to ACRNEMA.MAP in memory (last item, be aware of conflicting wildcard entries)
servercommand('put_amap:99,testserver,127.0.0.1,4433')

-- start log file
g = io.open('compressiontest.txt', 'wt')
g:write('servercomp', '\t', 'clientcomp', '\t', 'write', '\t', 'read', '\t', 'lossless', '\t', 'ratio', '\n')

for k,serversidecompression in ipairs(receivecompression) do
  for k2,clientsidecompression in ipairs(sendcompression) do
    -- create minimal server (4 files and a data folder)
    script('mkdir testserver')
    script('mkdir testserver\\data')
    filecopy('acrnema.map',  'testserver\\acrnema.map')
    filecopy('dgate.dic',    'testserver\\dgate.dic')
    filecopy('dicom.sql',    'testserver\\dicom.sql')
    syntax = '4'
    if string.sub(serversidecompression, 1, 1)=='n' then syntax=3 end
    f = io.open('testserver\\dicom.ini', 'wt')
    f:write([[
[sscscp]
MicroPACS                = sscscp
TCPPort                  = 4433
SqLite                   = 1
SQLServer                = testserver\testserver.db3
MAGDevice0               = testserver\Data\
UseBuiltInJPEG           = 1
TruncateFieldNames       = 10
FileNameSyntax           = ]]..syntax..[[

incomingcompression      = ]]..serversidecompression..[[
]])
    f:close()
    
    -- create serverside test program to uncompress all images
    f = io.open('testserver\\test.lua', 'wt')
    f:write([[
d = DicomObject:new()
for line in io.lines('testserver\\files.txt') do
  d:Read(line)
  d:Script('compression un')
  print(line)
end
    ]])
    f:close()
    
    -- initialize the test server's database and start it
    os.execute('dgate.exe -wtestserver -v -r')
    servercommand("luastart:os.execute('dgate -wtestserver -v')")
    sleep(100)

    -- get a test image and uncompress it
    d = DicomObject:new()
    d:Read(testimage)
    d:Script('compression un')
    d:Write('testserver\\testimage.dcm')
    dsize = filesize('testserver\\testimage.dcm')

    -- send it count times to test server
    print('compression', serversidecompression, clientsidecompression)
    t = os.clock()
    for i=0, count-1 do
      d.SOPInstanceUID = genuid()
      if (i%10)==0 then d.SeriesInstanceUID = genuid() end
      if (i%100)==0 then d.StudyInstanceUID = genuid() end
      d:Script('forward compressed as '.. clientsidecompression.. ' to testserver channel *')
    end
    sending = os.clock()-t

    -- list filenames of all files stored in test server
    os.execute('dgate.exe -wtestserver "--imagelister:local|||%s|testserver\\files.txt"')
    
    -- do a test read with uncompress in the test server
    t = os.clock()
    os.execute('dgate.exe -wtestserver "--lua:dofile([[testserver/test.lua]])"')
    readtime = os.clock()-t
    
    -- measure the compression on the first file
    e = DicomObject:new()
    for line in io.lines('testserver\\files.txt') do
      e:Read(line)
      ratio = filesize(line) / dsize
      e:Script('compression un')
      break
    end
    
    -- check if the compression was lossless
    d1 = d:GetImage(0)
    e1 = e:GetImage(0)
    lossless = d1==e1
    
    -- log the results
    g:write(serversidecompression, '\t', clientsidecompression, '\t', sending/count, '\t', readtime/count, '\t', tostring(lossless), '\t', ratio, '\n')
    
    -- remove the test server
    os.execute('dgate.exe -wtestserver --quit:')
    sleep(100)
    os.execute('del /q/s testserver\\*.*')
    os.execute('rmdir /q/s testserver')
  end
end
g:close()
