-- This script, when run from 
-- [lua] 
-- association=dofile('ChangeReturnIPAddress.lua')
-- will update the return adress for each AE to match the called 
-- address i.e., this will allow devices without fixed IP adress to
-- c-move images to them.

--[[ Test code; r-click evaluate in console after project-run:
Association.ConnectedIP = '5.5.5.5'
Association.Calling = 'RTDICOM01'
dofile('ChangeReturnIPAddress.lua')
for i=0,10 do
  print('AE', i, get_amap(i))
end
]]

local i
for i=0,100 do
  local AE,IP,P,C = get_amap(i)
  if AE==nil then break end
  print('testing AEs', i, AE, IP, P, C)
  if Association.Calling==AE and Association.ConnectedIP~=IP then
    print('changing AE to:', i, AE, Association.ConnectedIP, P, C)
    servercommand('put_amap:'..i..','..AE..','..Association.ConnectedIP..','..P..','..C)
  end
end
