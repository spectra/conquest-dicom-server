a=DicomObject:new()
a.QueryRetrieveLevel='STUDY'
a.StudyInstanceUID=''
a.StudyDate='20090101-20130404'
b=dicomquery('CONQUESTSRV1', 'STUDY', a)
f=io.open('file.txt', 'wt')
for i=0, #b-1 do
  f:write(b[i].StudyInstanceUID .. '\n')
end
f:close()