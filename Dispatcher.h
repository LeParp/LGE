#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "EventDispatcher.h"
#include "Events.h"

using Dispatcher = EventDispatcher<GameStarted,
                                   WindowCreated, WindowResized, KeyPressed,
                                   SetPlayable, Play,
                                   SetGround, SetDynamicBody, Impulse, Collided,
                                   SetRenderable, SetLighter, SetViewer, View>;

#endif // DISPATCHER_H
