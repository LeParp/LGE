#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "EventDispatcher.h"
#include "Events.h"

class Dispatcher : public EventDispatcher<GameStarted,
                                          WindowCreated, WindowResized,
                                          SetPlayable, Play,
                                          SetGround, SetDynamicBody, Move, Rotate, ApplyForce,
                                          SetRenderable, SetLighter, SetViewer, View>
{
};

#endif // DISPATCHER_H
