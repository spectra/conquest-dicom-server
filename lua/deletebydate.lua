x = DicomObject:new()
x.PatientName = ''
x.PatientID = ''
x.StudyDate = '20030101-20050322' -- date range match
x.PatientBirthDate = '19000101-19920322'
x.QueryRetrieveLevel = 'STUDY'
x.StudyInstanceUID = '' -- you want these returned for the loop
x.ModalitiesInStudy = ''

y = dicomquery('CONQUESTSRV1', 'STUDY', x)
-- now y is an array with all requested items

print('fixin to delete', #y, 'Studies')
for i=0, #y-1 do
  print('testing', y[i].PatientID, y[i].PatientName, y[i].StudyDate, y[i].ModalitiesInStudy)
  if string.find(y[i].ModalitiesInStudy, 'MG')==nil then
    z = DicomObject:new()
    z.PatientID = y[i].PatientID
    z.StudyInstanceUID = y[i].StudyInstanceUID
    print('deleting', y[i].PatientID, y[i].PatientName, y[i].StudyDate, y[i].ModalitiesInStudy)
   --dicomdelete(z)
  end
end
