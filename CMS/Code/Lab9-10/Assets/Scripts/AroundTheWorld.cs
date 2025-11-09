using UnityEngine;

public class AroundTheWorld : MonoBehaviour
{

    public GameObject wall;




    private void OnTriggerStay(Collider other)
    {
        if(other.name == "body")
        {
            wall.transform.Rotate(0, 1, 0);
        }
    }




    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        

        
    }
}
