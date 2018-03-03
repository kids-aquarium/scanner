using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JLEventTest : MonoBehaviour 
{

    // private member property area /////////////////////////////////

    private JLScanner myScanner;

    // public member property area //////////////////////////////////


    // private member method area ///////////////////////////////////


    private void fishReady()
    {
        Debug.Log("Fish is ready to read!");
    }


    // public member method area ////////////////////////////////////


    public void Start () 
    {
        myScanner = FindObjectOfType(typeof(JLScanner)) as JLScanner; 
	}

	
	// Update is called once per frame
    public void Update () 
    {
        if (Input.GetMouseButtonUp(0) == true)
        {
            myScanner.goFishing(fishReady);

            //myScanner.goFishingSync(fishReady);
        }

        transform.Rotate(0,Time.deltaTime*100,0);
	}


    // public event handling area //////////////////////////////////

}
