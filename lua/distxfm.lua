--[[ Sample of image processing; computes city block 
     distance transform ]]

--[[ To test; r-click evaluate in console after project-run:
d=DicomObject:new();
d:Read('c:\\1.dcm')
local t=os.clock() 
dofile('distxfm.lua')
print(os.clock()-t) 
d:Write('c:\\ta.dcm')
os.execute('"C:\\Program Files (x86)\\IrfanView\\i_view32.exe" c:\\ta.dcm')
]]

local rows = d.Rows
local cols = d.Columns
local a, i, j

for i=0,rows-1 do 
  a=d:GetRow(i) 
  for j=0,cols-1 do
    if a[j]>1700 then
      a[j]=0
    else
      a[j]=1000
    end      
  end 
  d:SetRow(i,0,a)
end

for i=0,rows-1 do 
  a=d:GetRow(i) 
  for j=1,cols-1 do
    a[j]=math.min(a[j], a[j-1]+1)
  end 
  for j=1,cols-1 do
    k = cols-1-j
    a[k]=math.min(a[k], a[k+1]+1)
  end 
  d:SetRow(i,0,a)
end

for i=0,cols-1 do 
  a=d:GetColumn(i)
  for j=1,rows-1 do
    a[j]=math.min(a[j], a[j-1]+1)
  end; 
  for j=1,rows-1 do
    k = rows-1-j
    a[k]=math.min(a[k], a[k+1]+1)
  end
  d:SetColumn(i,0,a)
end
