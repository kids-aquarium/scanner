using UnityEngine;
using UnityEngine.Events;
using System.Collections;
using System.Collections.Generic;

public class JLScanner:MonoBehaviour
{


    // private member property area /////////////////////////////////

    private JLEventManager eventManager;
    private bool isReadyToFishing;


    // public member property area //////////////////////////////////


    // private member method area ///////////////////////////////////


    private IEnumerator procGoFishing()
    {
        isReadyToFishing = false;

        Debug.Log("procGoFishing called.");

        for (int i = 0; i < 10;i++)
        {
            Debug.Log("Step " + i);

            yield return new WaitForSeconds(1);
        }

        eventManager.triggerEvent("readFish");

        isReadyToFishing = true;
    }

    private void procGoFishingSync()
    {
        Debug.Log("procGoFishing called.");

        for (int i = 0; i < 10; i++)
        {
            System.Threading.Thread.Sleep(1000);

            Debug.Log("Step " + i);
        }

        eventManager.triggerEvent("readFish");

        isReadyToFishing = true;
    }


    // public member method area ////////////////////////////////////

    public void Start()
    {
        isReadyToFishing = true;
    }


    public JLScanner()
    {
        eventManager = new JLEventManager();

        eventManager.startListening("goFishing", procGoFishingSync);
	}

    public void goFishingSync(UnityAction listener)
    {
        eventManager.startListening("readFish", listener);

        Debug.Log("goFishing called");

        eventManager.triggerEvent("goFishing");

        Debug.Log("goFishing return immediately???????");
    }
	
	
    public bool goFishing (UnityAction listener)
    {
        bool ret;

        ret = isReadyToFishing;

        if (isReadyToFishing == true)
        {
            isReadyToFishing = false;

            eventManager.startListening("readFish", listener);

            Debug.Log("goFishing called");

            StartCoroutine("procGoFishing");

            Debug.Log("goFishing return immediately");
        }
        else
        {
            Debug.Log("Previous action has not done yet!");
        }

        return ret;
	}

    // public event handling area //////////////////////////////////
}
