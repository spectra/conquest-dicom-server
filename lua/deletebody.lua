-- This script delete the 'BODY' contour in RTSTRUCT
--[[ To test; r-click evaluate in console after project-run:
readdicom('c:\\data\\rtstruct.dcm')
Data.Dump('c:\\data\\rtstruct_in.txt')
dofile('deletebody.lua')
Data.Dump('c:\\data\\rtstruct_out.txt')
]]

local roinumber, index, i
for i=0, #Data.StructureSetROISequence-1 do
  if Data.StructureSetROISequence[i].ROIName=='BODY' then
    roinumber = Data.StructureSetROISequence[i].ROINumber
    index = i
  end
end
Data.StructureSetROISequence[index]=nil
   
for i=0, #Data.ROIContourSequence-1 do
  if Data.ROIContourSequence[i].ReferencedROINumber==roinumber then
    index = i
  end
end
Data.ROIContourSequence[index]=nil

for i=0, #Data.RTROIObservationsSequence-1 do
  if Data.RTROIObservationsSequence[i].ReferencedROINumber==roinumber then
    index = i
  end
end
Data.RTROIObservationsSequence[index]=nil
