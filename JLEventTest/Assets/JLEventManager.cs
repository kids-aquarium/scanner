using UnityEngine;
using UnityEngine.Events;
using System.Collections;
using System.Collections.Generic;

// private member property area /////////////////////////////////

// public member property area //////////////////////////////////

// private member method area ///////////////////////////////////

// public member method area ////////////////////////////////////

// public event handling area //////////////////////////////////

public class JLEventManager
{


    // private member property area /////////////////////////////////


    private Dictionary<string, UnityEvent> eventDic;



    // public member property area //////////////////////////////////



    // private member method area ///////////////////////////////////



    // public member method area ////////////////////////////////////

    public JLEventManager()
    {
        if (eventDic == null)
        {
            eventDic = new Dictionary<string, UnityEvent>();
        }

        Debug.Log("JLEventManager created");
    }

    public void startListening(string eventName, UnityAction listener)
    {
        UnityEvent thisEvent;

        thisEvent = null;

        if (eventDic.ContainsKey(eventName) == false)
        {
            if (eventDic.TryGetValue(eventName, out thisEvent) == true)
            {
                thisEvent.AddListener(listener);
            }
            else
            {
                thisEvent = new UnityEvent();

                thisEvent.AddListener(listener);

                eventDic.Add(eventName, thisEvent);
            }
        }
        else{
            Debug.Log("The key is already existed");
        }
    }

    public void triggerEvent(string eventName)
    {
        UnityEvent thisEvent;

        thisEvent = null;

        if (eventDic.TryGetValue(eventName, out thisEvent))
        {
            thisEvent.Invoke();
        }
    }





    // public event handling area //////////////////////////////////
    

	

}
