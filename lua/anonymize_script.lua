-- =============================================================================
-- Anonymize DICOM tags to protect Private Health Information (HIPAA)
-- Based on:	DicomAnonymize.cq (c) Bart Hoekstra UMCG
-- Author: 	Marcel van Herk
-- Reference: 	PS 3.15-2009 Table E.1-1
-- Modification
-- 20120827	mvh	Use script() instead of os.execute() to avoid blinking window
-- 20130127	mvh	for 1.4.17beta: Match updated dictionary; added MaintainAge, MaintainSex, 
--			Reversible options; use lua crc calls
-- 20130211	mvh	Make sure PatientID used as filename has no invalid characters
-- 20130522	mvh	Cleanup for release; fixed when birthdate empty
-- 20130718	mvh	Set logroot not to c:\DicomAnonymized but to DicomAnonymized_Log
-- 20130813	mvh	Command line overrules generated patientid and patientname
-- 20140304	mvh	Remove OtherPatienIDSequence
-- 20140309	mvh	Protect against any missing data
-- =============================================================================

local scriptversion = "1.5; date 20140309"

---------------------------------- configuration -----------------------------
-- entries that show up in log but are NOT modified (except implicitly the UIDs)
local TagsToPrint = {
"FrameOfReferenceUID", "StudyInstanceUID", "SeriesInstanceUID", "SOPInstanceUID",
"Modality", "BodyPartExamined", "Manufacturer", "ManufacturerModelName",
"StudyDate", "StudyTime", "SeriesNumber", "ImageID"}

-- entries that are emptied
local TagsToEmpty = {
"AccessionNumber", "InstitutionName", "ReferringPhysicianName", "PerformingPhysicianName", "StudyID"}

-- entries that are removed
local TagsToRemove = {
"InstanceCreatorUID", "InstitutionAddress", "ReferringPhysicianAddress", "ReferringPhysicianTelephoneNumbers",
"StationName", "StudyDescription", --[["SeriesDescription",]] "InstitutionalDepartmentName",
"PhysiciansOfRecord", "NameOfPhysiciansReadingStudy", "OperatorsName", "AdmittingDiagnosesDescription",
"DerivationDescription", "OtherPatientIDs", "OtherPatientNames", "PatientAge",
"PatientSize", "PatientWeight", "MedicalRecordLocator", "EthnicGroup",
"Occupation", "AdditionalPatientHistory", "DeviceSerialNumber", "ProtocolName",
"ImageComments", "RequestAttributesSequence", "ContentSequence", "StorageMediaFileSetUID",
"PatientInsurancePlanCodeSequence", "PatientBirthName", "PatientAddress", "InsurancePlanIdentification",
"PatientMotherBirthName", "MilitaryRank", "BranchOfService", "RegionOfResidence",
"PatientTelephoneNumbers", "PatientComments", "StudyComments", "ScheduledPerformingPhysicianName",
"PerformingPhysicianIdentificationSequence", "OtherPatientIDsSequence" }

local MaintainAge = false
local MaintainSex = false
local reversible  = true
local logroot     = "DicomAnonymized_Log\\"

---------------------------------- end configuration -----------------------------

-- entries that show up in log and that are individually modified
local TagsToModify = {
"PatientID", "PatientName", "PatientBirthDate", "PatientSex"}

local function CRC32(val)
  return crc(tostring(val))
end;

-- remove characters that are not allowed in a filename
local pid = string.gsub(Data.PatientID, '[\\/:*?"<>|]', '_')

-- Log file handling (trailing backslash required for mkdir)
local logdir = logroot..pid.."\\";
-- 
local logfile = pid..'_'..(Data.StudyDate or '19700101')..'_'..(Data.Modality or 'UN')..'_'..(Data.SOPInstanceUID or 'unknown')..'.log'
script('mkdir '..logdir);

local f = io.open(logdir .. logfile, "wt");
f:write("DicomAnonymize.lua script version: ", scriptversion, "\n")
f:write("Logfile name                     : ", logfile, "\n")
f:write("Logfile created                  : ", os.date(), "\n")

-- Check dictionary
for key2, val2 in ipairs({TagsToModify, TagsToPrint, TagsToEmpty, TagsToRemove}) do
  for key, val in ipairs(val2) do 
    if dictionary(val)==nil and string.sub(val,1,1)~='0' then 
      f:write("*** Error: '", val, "' not in dictionary\n")
    end
  end
end

-- Log data in original object
f:write("===== ORIGINAL DICOM DATA =====\n");
for key2, val2 in ipairs({TagsToModify, TagsToPrint, TagsToEmpty, TagsToRemove}) do
  for key, val in ipairs(val2) do 
    f:write(val, ': ', tostring(Data[val]), "\n")
   end
end

-- modify and log modified object
f:write("===== MODIFIED DICOM DATA =====\n");
script('newuids'); 
f:write("Generated new UIDs\n")

if Data.PatientBirthDate==nil or Data.PatientBirthDate=='' then 
  Data.PatientBirthDate='00000000' 
end

-- the changes in patient ID etc are hardcoded
local pre = CRC32(Data.PatientID)..'.'..CRC32(Data.PatientBirthDate);
local pne = 'PAT'..CRC32(Data.PatientID)
if version and command_line and command_line~='' then pre=command_line end
if version and command_line and command_line~='' then pne=command_line end

if Data.PatientName~='' then
  if reversible==true then
    Data.PatientName = changeuid(Data.PatientName, pne)
  else
    Data.PatientName = pne;
  end
  f:write('Anonymized PatientName to: ', Data.PatientName, "\n");
end
if Data.PatientID~='' then
  if reversible==true then
    Data.PatientID = changeuid(Data.PatientID, pre)
  else
    Data.PatientID = pre;
  end
  f:write('Anonymized PatientID to: ', Data.PatientID, "\n");
end
if Data.PatientBirthDate~='' then
  local org = Data.PatientBirthDate;
  if MaintainAge==true then
    Data.PatientBirthDate = string.sub(org, 1, 4)..'0101'
  else
    Data.PatientBirthDate = '';
  end
  if reversible==true then
    changeuid(pre..'.bd.'..org, pre..'.bd.'..Data.PatientBirthDate)
  end	      
  f:write('Changed patient birthdate to: ', tostring(Data.PatientBirthDate), "\n");
end
if (MaintainSex==false) and (Data.PatientSex~='') then
  local org = Data.PatientSex or 'UN';
  Data.PatientSex = '';
  f:write('Made patient sex empty: ', tostring(Data.PatientSex), "\n");
  if reversible==true then
    changeuid(pre..'.ps.'..org, pre..'.ps.'..Data.PatientSex)
  end	      
end

-- log modified UIDs
local i;
for i=1, 4 do
  f:write(TagsToPrint[i], ': ', tostring(Data[TagsToPrint[i]]), "\n");
end
-- empty tags
for key, val in ipairs(TagsToEmpty) do
  Data[val]='';
  f:write('Made ', val, ' empty: ', tostring(Data[val]), "\n");
end
-- remove tags
for key, val in ipairs(TagsToRemove) do
  Data[val]=nil;
  f:write('Removed ', val, ': ', tostring(Data[val]), "\n");
end

f:close();
