#pragma once

#include <list>
#include <boost/thread/mutex.hpp>

template<class Event_Type>
class EventServer;

template<class Event_Type>
class EventObserver
{
	EventServer<Event_Type> *_server;
protected:
	EventServer<Event_Type> *getServer();
	void send(Event_Type&);
public:
	virtual void notify(Event_Type&) = 0;
};


//Thread Safetry class
template<class Event_Type>
class EventServer
{
	typedef typename std::list<EventObserver<Event_Type>*>::iterator list_iterator;
	std::list<EventObserver<Event_Type>*> observers;
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		boost::mutex mutex;
	#endif
protected:
	bool hasObserver(EventObserver<Event_Type>*);
	list_iterator findObserver(EventObserver<Event_Type>*);
	EventServer();
public:
	void notify(Event_Type&);
	void subscribe(EventObserver<Event_Type>*);
	void unsubscribe(EventObserver<Event_Type>*);
	~EventServer();
};

#include "EventServer.cpp"