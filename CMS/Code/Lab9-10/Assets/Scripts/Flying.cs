using UnityEngine;

public class Flying : MonoBehaviour
{


    public float coreSpeed = 1f;
    public GameObject exp1;

    private void OnCollisionEnter(Collision col)
    {
        if (col.gameObject.tag == "goal")
        {
            GetComponent<Renderer>().enabled = false;

            col.gameObject.GetComponent<Renderer>().material.color = new Color(1, 0, 0);

            Instantiate(exp1, gameObject.transform);


            AudioSource.PlayClipAtPoint(gameObject.GetComponent<AudioSource>().clip, gameObject.transform.position);


        }
    }




            // Start is called once before the first execution of Update after the MonoBehaviour is created
            void Start()
    {
        Destroy(gameObject, 5);
    }

    // Update is called once per frame
    void Update()
    {
        transform.position += transform.TransformDirection(Vector3.up * coreSpeed);
    }
}
