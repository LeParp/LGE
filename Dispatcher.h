#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "EventDispatcher.h"
#include "Events.h"

class Dispatcher : public EventDispatcher<GameStarted,
                                          WindowCreated, WindowResized,
                                          MeshAdded, LightAdded, CameraAdded,
                                          PlayerAdded>
{
};

#endif // DISPATCHER_H
