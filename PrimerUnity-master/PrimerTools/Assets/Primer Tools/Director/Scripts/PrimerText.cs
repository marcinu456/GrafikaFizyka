﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class PrimerText : PrimerObject
{
    public bool billboard;
    public TextMeshPro tmpro;
    
    protected override void Awake() {
        base.Awake();
        //This script assumes it's on a prefab with a TextMeshPro component
        tmpro = GetComponent<TextMeshPro>();
    }
    void Update()
    {
        if (billboard) {
            transform.rotation = Quaternion.LookRotation(
                transform.position - Camera.main.transform.position, 
                transform.parent.up
            );
        }
    }
}
