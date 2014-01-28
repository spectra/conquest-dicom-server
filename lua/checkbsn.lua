-- check where Dutch BSN is used as PatientID in CareStream, 
-- mvh 20120424
-- mvh+mb+cp 201200713: some more prints; mask virtual 
-- servers from RT systems

pacs = 'avlpacsFIR';

--initiate query
b=newdicomobject(); 
b.PatientID = ''; 
b.StudyInstanceUID=''; 
b.StudyDate=''; 
b.OtherPatientIDsSequence={}; 
b.OtherPatientIDsSequence[0].PatientID=''; 
b.StudyDate='20120101-20120712';

print('****** quering', pacs, 'date=', b.StudyDate);
if pacs~='avlpacsFIR' then
  b['9999,0802']=0; -- set virtualserver mask to 0
end;
b.QueryLevel='STUDY'; 

--do the study query
a=dicomquery(pacs, 'STUDY', b); 
print('****** query done, records = ', #a);

function q(s, index)
  return string.byte(s, index)-string.byte('0')
end;

--for each study
for i=0,#a-1 do
    s = a[i].PatientID;
    if (#s==9) then
      check = q(s,1)*9+q(s,2)*8+q(s,3)*7+q(s,4)*6+q(s,5)*5+q(s,6)*4+q(s,7)*3+q(s,8)*2-q(s,9)*1;
      if math.modf(check/11)==check/11 then
        print('Processing study', a[i].PatientID, a[i].StudyInstanceUID, a[i].StudyDate);

        -- initiate an image query
        c=newdicomobject(); 
        c.PatientID = a[i].PatientID; 
        c.StudyInstanceUID = a[i].StudyInstanceUID;
        c.SOPInstanceUID = "";
        if pacs~='avlpacsFIR' then
		  c['9999,0802']=0; -- set virtualserver mask to 0
		end;
        d=dicomquery(pacs, 'IMAGE', c);

        -- initiate a move of the first image
        print('Processing first image', a[i].PatientID, SOPInstanceUID, 'of images: ', #d);
        SOPInstanceUID = d[0].SOPInstanceUID;
        d[0].QueryRetrieveLevel = 'IMAGE';
        if pacs~='RTDICOM01' then 
		  dicommove(pacs, 'RTDICOM01', d[0]);
		end;

 
        -- test that the move was succesful
--[[        c=newdicomobject(); 
        c.PatientID = a[i].PatientID; 
        c.StudyInstanceUID = a[i].StudyInstanceUID;
        c.SOPInstanceUID = SOPInstanceUID;
]]
        d=dbquery("DICOMImages", "SOPInstanc", "ImagePat='"..a[i].PatientID.."' and SOPInstanc='"..SOPInstanceUID.."'");
        if #d==0 then
          print('***** error', a[i].PatientID, a[i].StudyInstanceUID, SOPInstanceUID, a[i].StudyDate);
        else
          -- read the image into memory and log the mapping
          e=newdicomobject();
          e:Read(a[i].PatientID..':'..SOPInstanceUID);
          if e.OtherPatientIDsSequence~=nil then
            print('***** got', a[i].PatientID, e.OtherPatientIDsSequence[0].PatientID, a[i].StudyDate)
          else
            print('***** no-id', a[i].PatientID, a[i].StudyInstanceUID, SOPInstanceUID, a[i].StudyDate);
          end;
        end;
      end;
    end
end;
print('***** done');
