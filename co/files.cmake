
# Copyright (c) 2010 Cedric Stalder <cedric.stalder@gmail.ch>
#               2011-2013 Stefan Eilemann <eile@eyescale.ch>
#               2012 Daniel Nachbaur <danielnachbaur@gmail.com>

set(CO_PUBLIC_HEADERS
  api.h
  array.h
  barrier.h
  buffer.h
  bufferConnection.h
  bufferListener.h
  co.h
  commandFunc.h
  commandQueue.h
  commands.h
  connection.h
  connectionDescription.h
  connectionSet.h
  connectionType.h
  customICommand.h
  customOCommand.h
  dataIStream.h
  dataIStream.ipp
  dataIStreamArchive.h
  dataIStreamArchive.ipp
  dataOStream.h
  dataOStream.ipp
  dataOStreamArchive.h
  dataOStreamArchive.ipp
  dataStreamArchiveException.h
  defines.h
  dispatcher.h
  exception.h
  global.h
  iCommand.h
  init.h
  localNode.h
  log.h
  node.h
  nodeType.h
  oCommand.h
  object.h
  objectFactory.h
  objectHandler.h
  objectICommand.h
  objectMap.h
  objectOCommand.h
  objectVersion.h
  queueItem.h
  queueMaster.h
  queueSlave.h
  sendToken.h
  serializable.h
  types.h
  worker.h
  worker.ipp
  zeroconf.h
  )

set(CO_HEADERS
  barrierCommand.h
  bufferCache.h
  connectionListener.h
  dataStreamArchive.h
  dataIStreamQueue.h
  deltaMasterCM.h
  eventConnection.h
  fullMasterCM.h
  instanceCache.h
  masterCMCommand.h
  nodeCommand.h
  nullCM.h
  objectCM.h
  objectDataICommand.h
  objectDataOCommand.h
  objectDataIStream.h
  objectDataOStream.h
  objectDeltaDataOStream.h
  objectInstanceDataOStream.h
  objectSlaveDataOStream.h
  objectStore.h
  pipeConnection.h
  queueCommand.h
  rspConnection.h
  socketConnection.h
  staticMasterCM.h
  staticSlaveCM.h
  unbufferedMasterCM.h
  versionedMasterCM.h
  versionedSlaveCM.h
  )

set(CO_SOURCES
  barrier.cpp
  buffer.cpp
  bufferCache.cpp
  bufferConnection.cpp
  commandQueue.cpp
  connection.cpp
  connectionDescription.cpp
  connectionSet.cpp
  customICommand.cpp
  customOCommand.cpp
  dataIStream.cpp
  dataIStreamQueue.cpp
  dataOStream.cpp
  deltaMasterCM.cpp
  dispatcher.cpp
  eventConnection.cpp
  fullMasterCM.cpp
  global.cpp
  iCommand.cpp
  init.cpp
  instanceCache.cpp
  localNode.cpp
  masterCMCommand.cpp
  node.cpp
  oCommand.cpp
  object.cpp
  objectCM.cpp
  objectDataICommand.cpp
  objectDataIStream.cpp
  objectDataOCommand.cpp
  objectDataOStream.cpp
  objectDeltaDataOStream.cpp
  objectHandler.cpp
  objectICommand.cpp
  objectInstanceDataOStream.cpp
  objectMap.cpp
  objectOCommand.cpp
  objectSlaveDataOStream.cpp
  objectStore.cpp
  objectVersion.cpp
  pipeConnection.cpp
  queueItem.cpp
  queueMaster.cpp
  queueSlave.cpp
  sendToken.cpp
  serializable.cpp
  socketConnection.cpp
  staticSlaveCM.cpp
  unbufferedMasterCM.cpp
  version.cpp
  versionedMasterCM.cpp
  versionedSlaveCM.cpp
  worker.cpp
  zeroconf.cpp
  )

if(WIN32)
  list(APPEND CO_HEADERS namedPipeConnection.h)
  list(APPEND CO_SOURCES namedPipeConnection.cpp)
else()
  list(APPEND CO_HEADERS fdConnection.h)
  list(APPEND CO_SOURCES fdConnection.cpp)
endif()
