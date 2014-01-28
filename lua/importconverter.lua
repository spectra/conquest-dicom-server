if Data.ProtocolName == "RTP Retrospective Gating" then
   str = Data.SeriesDescription
   str = str:match('[^/]*' )
   Data.SeriesDescription = str
   print (Data.SeriesDescription)
   print (str)
end