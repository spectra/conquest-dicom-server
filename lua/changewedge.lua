-- This script modifies 'STANDARD' wedges to 'MOTORIZED' in RTPLAN
--[[ To test; r-click evaluate in console after project-run:
readdicom('c:\\data\\rtplan.dcm')
Data.Dump('c:\\data\\rtplan_in.txt')
dofile('changewedge.lua')
Data.Dump('c:\\data\\rtplan_out.txt')
]]

if Data.Modality=='RTPPLAN' then
  print('Processing RTPLAN for patient ' .. Data.PatientName .. ' ' .. Data.PatientID);
  print('Date of RTPLAN is ' .. Data.RTPlanDate);
  
  local i
  for i=0, #Data.BeamSequence-1 do
    if Data.BeamSequence[i].WedgeSequence then
      print('Wedge type in beam ' .. i .. ' is ' .. Data.BeamSequence[i].WedgeSequence[0].WedgeType);
      if Data.BeamSequence[i].WedgeSequence[0].WedgeType == 'STANDARD' then
        Data.BeamSequence[i].WedgeSequence[0].WedgeType = 'MOTORIZED'
      end
      print('Modified wedge type in beam ' .. i .. ' to ' .. Data.BeamSequence[i].WedgeSequence[0].WedgeType)
    end
  end
end
