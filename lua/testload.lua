-- high load test of a dicom server
t = os.clock()

if p==nil then
  for j=1,3 do servercommand("luastart:p="..j..";dofile('c:/dicomserver/lua/testload.lua')") end
  return
end

x = DicomObject:new()
x:Read('c:\\t.dcm')
--x:Script('compression jl')
for i=0, 1000 do
  x.SOPInstanceUID = genuid()..p
  if (i%1000)==0 then x.SeriesInstanceUID = genuid()..p end
  if (i%1000)==0 then x.StudyInstanceUID = genuid()..p end
  x:Script('forward to CONQUESTSRV1 channel *')
  --x:AddImage()
  print(i)
  
--  b=newdicomobject(); b.PatientName = '*'; a=dicomquery('CONQUESTSRV1', 'PATIENT', b);
--  print ('First query result has this patientname:', a[0].PatientName);
--  
--  b=newdicomobject(); b.PatientName = 'HEAD EXP2'; b.QueryRetrieveLevel = 'STUDY'; dicommove('CONQUESTSRV1', 'DENCOMROUTER', b, 0, 'print(Global.StatusString)');
end

print('*** time lapse', os.clock()-t)
