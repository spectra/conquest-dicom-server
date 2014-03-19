--[[add the following 2 lines to dicom.ini for automatic processing of series sent to server after 10 s
[lua]
importconverter0 = if Association.Called=="CONQUESTSRV!" then script("process series after 10 by lua/niftytest.lua " .. Data.PatientID .. ":" .. Data.SeriesInstanceUID) end
]]--

require('niftyutil')
require('niftydicom')

command_line = command_line or 'testpat:1.3.12.2.1107.5.1.4.28001.4.0.3215162956741568'
print('processing', command_line)

local t = split(command_line, ':')
x = DicomObject:new()
x.QueryRetrieveLevel = 'IMAGE'
x.PatientID = t[1]
x.SeriesInstanceUID = t[2]
x.SOPInstanceUID = ''
y = dicomquery('CONQUESTSRV1', 'IMAGE', x)
names = {}
for i=0, #y-1 do 
  names[i+1] = y[i].PatientID .. ':' .. y[i].SOPInstanceUID
end
table.sort(names)

write_nifty(names, 'c:\\data\\test.nii')
osexecute('"C:\\Program Files\\NiftyReg\\bin\\reg_tools.exe" -in c:\\data\\test.nii -out c:\\data\\test.nii -smoG 2 2 1')

reread_nifty(names, 'c:\\data\\test.nii', false, {SeriesDescription = 'Smoothed by reg_tools', SeriesNumber = 100})
