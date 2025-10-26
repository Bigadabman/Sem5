
using UnityEngine;
using UnityEngine.EventSystems;

public class CubeClics : MonoBehaviour, IPointerClickHandler
{

   


    public void OnPointerClick(PointerEventData eventData)
    {

        float red = Random.Range(.0f, 1.0f);
        float green = Random.Range(.0f, 1.0f);
        float blue = Random.Range(.0f, 1.0f);
        Color col1 = new Color(red, green, blue);
        GetComponent<Renderer>().material.color = col1;


        Vector3 target = eventData.pointerPressRaycast.worldPosition;
        Vector3 collid = Camera.main.transform.position;

        int force = 500;

        Vector3 distance = target - collid;
        distance = distance.normalized;

        collid = distance * force;

        gameObject.GetComponent<Rigidbody>().AddForceAtPosition(collid, target);



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
