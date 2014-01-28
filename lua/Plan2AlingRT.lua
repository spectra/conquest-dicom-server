--[[
Date        Name        Description
20120330   mvh + cp    Created script for forwarding RTPLAN and RTSTRUCT to AlignRT PC
]]--

print('checking for alignRT')
if Data.Modality == "RTPLAN" and string.find(Data.RTPlanDescription, ' A1')~=NIL then
   -- print (Data.ReferencedStructureSetSequence[0].ReferencedSOPInstanceUID)

   -- Read StructureSet
   StructureSet = newdicomobject()
   StructureSet:Read(Data.PatientID..':'..Data.ReferencedStructureSetSequence[0].ReferencedSOPInstanceUID);

    -- Query SeriesDescription
   local SeriesUID = (StructureSet.ReferencedFrameOfReferenceSequence[0].RTReferencedStudySequence[0].RTReferencedSeriesSequence[0].SeriesInstanceUID)
    local SeriesDesc = dbquery('DICOMSeries', 'SeriesDesc', 'SeriesInst = "'..SeriesUID..'"')[1][1]
   print (SeriesDesc)

   s = string.find(SeriesDesc, "mamBreath")
   if s~=NIL then
      -- Send RTSTRUCT
      b=newdicomobject(); 
      b.PatientID = Data.PatientID;
      b.SOPInstanceUID = StructureSet.SOPInstanceUID
      b.QueryRetrieveLevel = 'IMAGE'; dicommove('SDA05365','SGALINGALE' , b);
     
      -- Send RTPLAN
      b=newdicomobject(); 
      b.PatientID = Data.PatientID;
      b.SOPInstanceUID = Data.SOPInstanceUID
      b.QueryRetrieveLevel = 'IMAGE'; dicommove('SDA05365','SGALINGALE' , b);
      print('RTPLAN and RTSTUCT is sent to AlignRTA1')
   end;
end
