template<class Event_Type>
EventServer<Event_Type>::EventServer() {}

template<class Event_Type>
void EventServer<Event_Type>::notify(Event_Type &e)
{
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		mutex.lock();
	#endif
		for (list_iterator i = observers.begin(); i != observers.end(); ++i)
		{
			i->notify(e);
		}
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		mutex.unlock();
	#endif
}

template<class Event_Type>
typename EventServer<Event_Type>::list_iterator EventServer<Event_Type>::findObserver(EventObserver<Event_Type> *obs)
{
	for (list_iterator i = observers.begin(); i != observers.end(); ++i)
	{
		if(*i == obs) return i;
	}

	return observers.end();
}

template<class Event_Type>
void EventServer<Event_Type>::subscribe(EventObserver<Event_Type> *obs)
{
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		mutex.lock();
	#endif
		if(hasObserver(obs)) return;
		observers.push_front(obs);
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		mutex.unlock();
	#endif
}

template<class Event_Type>
bool EventServer<Event_Type>::hasObserver(EventObserver<Event_Type> *obs)
{
	return (findObserver(obs) != observers.end()) ? true : false;
}

template<class Event_Type>
void EventServer<Event_Type>::unsubscribe(EventObserver<Event_Type> *obs)
{
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		mutex.lock();
	#endif
		if(!hasObserver(obs)) return;
		observers.erase(findObserver(obs));
	#ifdef ENABLE_THREAD_SEFETRY_EVENT_SERVER
		mutex.unlock();
	#endif
}

template<class Event_Type>
EventServer<Event_Type>::~EventServer() {}