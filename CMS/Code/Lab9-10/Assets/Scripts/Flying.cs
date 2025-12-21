using UnityEngine;

public class Flying : MonoBehaviour
{


    public float coreSpeed = 0.0001f;
    public GameObject exp1;

    bool hasHit = false;

    private void OnCollisionEnter(Collision col)
    {
       // if (hasHit) return;

        //hasHit = true;
        if (col.gameObject.tag == "goal" || col.gameObject.tag == "Player")
        {

            Instantiate(exp1, gameObject.transform);


            AudioSource.PlayClipAtPoint(gameObject.GetComponent<AudioSource>().clip, gameObject.transform.position);


        }

        Instantiate(exp1, gameObject.transform);


        AudioSource.PlayClipAtPoint(gameObject.GetComponent<AudioSource>().clip, gameObject.transform.position);


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
