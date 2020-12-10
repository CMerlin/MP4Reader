add_executable(exe_bin ./MP4.CO64.cpp 
MP4.ELST.cpp   
MP4.HDLR.cpp 
MP4.MDAT.cpp 
MP4.PADB.cpp  
MP4.SCHI.cpp 
MP4.STDP.cpp
MP4.STTS.cpp 
MP4.TREF.cpp   
MP4.XML.cpp       
MP4.ContainerAtom.cpp
MP4.File.cpp  
MP4.HMHD.cpp 
MP4.MDHD.cpp
mp4parse.cpp 
MP4.SCHM.cpp 
MP4.STSC.cpp 
MP4.STZ2.cpp 
MP4.TREX.cpp              
MP4.CPRT.cpp    
MP4.FREE.cpp   
MP4.IINF.cpp 
MP4.MEHD.cpp 
MP4.Parser.cpp 
MP4.SDTP.cpp 
MP4.STSD.cpp 
MP4.SUBS.cpp 
MP4.TRUN.cpp
MP4.Atom.cpp    
MP4.CTTS.cpp  
MP4.FRMA.cpp    
MP4.ILOC.cpp 
MP4.MFHD.cpp 
MP4.PDIN.cpp  
MP4.SGPD.cpp  
MP4.STSH.cpp 
MP4.TFHD.cpp 
MP4.UDTA.cpp
MP4.BinaryStream.cpp 
MP4.DataAtom.cpp    
MP4.FTYP.cpp   
MP4.IMIF.cpp 
MP4.MFRO.cpp 
MP4.PITM.cpp 
MP4.SMHD.cpp 
MP4.STSS.cpp 
MP4.TFRA.cpp 
MP4.UnknownAtom.cpp
MP4.BXML.cpp     
MP4.DREF.cpp   
MP4.FullBox.cpp 
MP4.IPMC.cpp 
MP4.MVHD.cpp 
MP4.SBGP.cpp  
MP4.STCO.cpp  
MP4.STSZ.cpp 
MP4.TKHD.cpp 
MP4.VMHD.cpp)

#add_executable(printInfo ./main.cpp ./print.cpp)
#add_executable(mainStarter ./mainStarter/main.cc ./mainStarter/Starter.cc)
#target_link_libraries(mainStarter gdlp_base gdlp_adpters)
#install(TARGETS mainStarter  DESTINATION bin)

#add_executable(protocolParser ./protocols/main.cc ./protocols/protocolParser.cc  ./protocols/protocolParserLua.cc)
#add_executable(protocolParser ./protocols/main.cc ./protocols/protocolParser.cc)
#target_link_libraries(protocolParser gdlp_base gdlp_adpters lua dl boost_program_options quarterLuaCppFunction)
#install(TARGETS protocolPraser  DESTINATION bin)

