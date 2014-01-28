require "pack"
dofile('nifty.lua')

-- query all series
x=DicomObject:new()
x.QueryRetrieveLevel='SERIES'
x.PatientID='VeiCat'
x.SOPInstanceUID=''
x.SeriesInstanceUID=''
x.SeriesTime=''
y=dicomquery('CONQUESTSRV1', 'SERIES', x)

-- select and sort all longer series on time
t = {}
for i=0,#y-1 do
  -- query just to count
  z=DicomObject:new()
  z.QueryRetrieveLevel='IMAGE'
  z.PatientID=y[i].PatientID
  z.SOPInstanceUID=''
  z.SeriesInstanceUID=y[i].SeriesInstanceUID
  u=dicomquery('CONQUESTSRV1', 'IMAGE', z)
  if #u>20 then
    table.insert(t, {y[i].SeriesInstanceUID, y[i].SeriesTime})
  end
end
table.sort(t, function(a, b) return a[2]<b[2] end)

-- this will will log all converted slices
f = io.open('converted\\' .. x.PatientID .. '_timestamps.txt', 'wt')

start = 0;
for i=1, #t do
  names = {}
  outnames = {}
  
  -- query to get AcquisitionTime and InstanceUID for each slice
  z=DicomObject:new()
  z.QueryRetrieveLevel='IMAGE'
  z.PatientID=x.PatientID
  z.SOPInstanceUID=''
  z.SeriesInstanceUID=t[i][1]
  z.AcquisitionTime=''
  u=dicomquery('CONQUESTSRV1', 'IMAGE', z)
  for j=0,#u-1 do
    names[j+1] = {u[j].PatientID..':'..u[j].SOPInstanceUID, u[j].AcquisitionTime}
  end
  
  -- sort slices on acquisitiontime
  table.sort(names, function(a, b) return a[2]<b[2] end)
  
  -- tag each slice with a sequence number
  for j=1,#names do
    names[j][3] = j+start-1
    outnames[j] = string.format('converted\\%s_%05d.nii', x.PatientID, j+start-1)
  end
  start = start + #u
  
  print(unpack(names[1]))
  write_nifty(names, outnames, 3) -- outnames table --> mode where each slice is converted
  
  -- log the processed data
  for j=1,#names do
    names[j]=table.concat(names[j], ',')
  end
  f:write(table.concat(names, '\n'))
  f:write('\n\n')
end

f:close();
