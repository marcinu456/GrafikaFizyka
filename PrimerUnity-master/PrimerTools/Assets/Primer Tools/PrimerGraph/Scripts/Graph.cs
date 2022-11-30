﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEditor;
using UnityEngine;

/* TODO 
 * (Core)
 * Add precision options for tic labels
 * 
 * (When needed)
 * Make padding amount uniform instead of using fraction of each axis length (maybe)
 * Destroy unused tics, animating them to zero scale 
 */  

public class Graph : PrimerObject
{
    //Welcome to the land of way too many public variables.
    [Header("X")] 
    public float xMin;
    public float xMax;
    public float xTicStep;
    public string xAxisLabelString;
    public string xAxisLabelPos;
    public bool xHidden;
    public float xAxisLength;
    //Calculated alignment shortcuts
    public float xLengthMinusPadding;
    public float xAxisOffset;
    public float xDrawnMin;

    [Header("Y")] 
    public float yMin;
    public float yMax;
    public float yTicStep;
    public string yAxisLabelString;
    public string yAxisLabelPos;
    public bool yHidden;
    public float yAxisLength;
    //Calculated alignment shortcuts
    public float yLengthMinusPadding;
    public float yAxisOffset;

    [Header("Z")] 
    public float zMin;
    public float zMax;
    public float zTicStep;
    public string zAxisLabelString;
    public string zAxisLabelPos;
    public bool zHidden;
    public float zAxisLength;
    //Calculated alignment shortcuts
    public float zLengthMinusPadding;
    public float zAxisOffset;
    public float zDrawnMin;

    internal bool manualTicMode;

    public Dictionary<float, string> manualTicsX;
    public Dictionary<float, string> manualTicsY;
    public float ticLabelDistanceVertical;
    public float ticLabelDistanceHorizontal;
    public float ticLabelSize;
    public string arrows;
    public float paddingFraction;
    public bool rightHanded;

    public Axes axesHandler;
    public GameObject arrowPrefab;

    public CurveData curveDataPrefab;
    public LineRenderer lrPrefab;
    public Dictionary<string, CurveData> curves = new Dictionary<string, CurveData>();

    public SurfaceData surfaceDataPrefab;
    public Dictionary<string, SurfaceData> surfaces = new Dictionary<string, SurfaceData>();

    public StackedAreaData stackedAreaDataPrefab;
    public Dictionary<string, StackedAreaData> stackedAreas = new Dictionary<string, StackedAreaData>();

    public PointData pointData;
    public bool labelsFaceCamera;
    public List<PrimerObject> allLabels = new List<PrimerObject>();

    void Update() {
        if (labelsFaceCamera) {
            //Vector3 diffVec = Camera.main.transform.position - transform.position;
            //Vector3 rotEuler = Quaternion.LookRotation(diffVec).eulerAngles;
            Quaternion labelRot = Quaternion.Euler(0, Camera.main.transform.rotation.eulerAngles.y, 0);
            foreach (PrimerObject p in allLabels) {
                p.RotateTowardsWithInertia(labelRot, global: true);
            }
        }
    }

    public void Initialize(
        Func<float, float, float>[] initialSurfaceFunctions = null, //Not implemented
        Func<float, float>[] initialCurveFunctions = null, //Not implemented
        Vector3[] initialPoints = null, //Not implemented

        float xMin = 0f,
        float xMax = 10f,
        string xAxisLabelString = "x",
        string xAxisLabelPos = "end", //end or end
        float xAxisLength = 1f, //Axis lengths and are the main tool for controlling size, since changing the graph's scale can warp component objects
        float xTicStep = 2f,
        bool xHidden = false,
        
        float yMin = 0f,
        float yMax = 10f,
        string yAxisLabelString = "y",
        string yAxisLabelPos = "end", //end or along
        float yAxisLength = 1f, //Axis lengths and are the main tool for controlling size, since changing the graph's scale can warp component objects
        float yTicStep = 2f,
        bool yHidden = false,
        
        float zMin = 0f,
        float zMax = 10f,
        string zAxisLabelString = "z",
        string zAxisLabelPos = "end", //end or along
        float zAxisLength = 1f, //Axis lengths and are the main tool for controlling size, since changing the graph's scale can warp component objects
        float zTicStep = 2f,
        bool zHidden = false,
        
        int ticPrecision = 0, //Not implemented
        float ticLabelDistanceVertical = 0.25f, //For horizontally aligned axes
        float ticLabelDistanceHorizontal = 0.65f, //For the vertically aligned axis
        float ticLabelSize = 1f,
        //Similar for y and z
        float scale = 1, //Scale is float because it will be uniform in all directions to avoid warping. Axis length and tic units are determined elswhere.
        
        bool manualTicMode = false,

        float paddingFraction = 0.05f, //How much of the total length is allocated to extending axes/arrows beyond the data range
        string arrows = "both",

        bool rightHanded = true
    )
    {
        this.paddingFraction = paddingFraction;
        this.xMin = xMin;
        this.xMax = xMax;
        //Debug.Log("Hey, you called Graph.Initialize");
        this.xAxisLength = xAxisLength;
        this.xTicStep = xTicStep;
        this.xAxisLabelString = xAxisLabelString;
        this.xAxisLabelPos = xAxisLabelPos;
        this.xHidden = xHidden; 
        this.xLengthMinusPadding = this.xAxisLength * (1 - 2 * this.paddingFraction);
        //Offset is padding plus the padded/scaled min
        this.xAxisOffset = - this.xAxisLength * this.paddingFraction + this.xMin * this.xLengthMinusPadding / (this.xMax - this.xMin);
        this.xDrawnMin = this.xAxisOffset + this.xAxisLength * paddingFraction;

        this.yMin = yMin;
        this.yMax = yMax;
        //Debug.Log("Hey, you called Graph.Initialize");
        this.yAxisLength = yAxisLength;
        this.yTicStep = yTicStep;
        this.yAxisLabelString = yAxisLabelString;
        this.yAxisLabelPos = yAxisLabelPos;
        this.yHidden = yHidden;
        this.yLengthMinusPadding = this.yAxisLength * (1 - 2 * this.paddingFraction);
        //Offset is padding plus the padded/scaled min
        this.yAxisOffset = -this.yAxisLength * this.paddingFraction + this.yMin * this.yLengthMinusPadding / (this.yMax - this.yMin);

        this.zMin = zMin;
        this.zMax = zMax;
        //Debug.Log("Hey, you called Graph.Initialize");
        this.zAxisLength = zAxisLength;
        this.zTicStep = zTicStep;
        this.zAxisLabelString = zAxisLabelString;
        this.zAxisLabelPos = zAxisLabelPos;
        this.zHidden = zHidden;
        this.zLengthMinusPadding = this.zAxisLength * (1 - 2 * this.paddingFraction);
        //Offset is padding plus the padded/scaled min
        this.zAxisOffset = -this.zAxisLength * this.paddingFraction + this.zMin * this.zLengthMinusPadding / (this.zMax - this.zMin);
        this.zDrawnMin = this.zAxisOffset + this.zAxisLength * paddingFraction;

        this.ticLabelDistanceVertical = ticLabelDistanceVertical;
        this.ticLabelDistanceHorizontal = ticLabelDistanceHorizontal;
        this.ticLabelSize = ticLabelSize;
        this.arrows = arrows;

        this.manualTicMode = manualTicMode;

        this.rightHanded = rightHanded;

        axesHandler.graph = this;
        axesHandler.SetUpAxes();
        
        //Set scale
        //Intrinsic scale determines base size and doesn't vary during animations
        this.intrinsicScale = new Vector3(scale, scale, scale);
        transform.localScale = this.intrinsicScale;
    }

    /// <summary>
    /// Adds a new curve with a given id. If an existing curve with that id already exist, return the existing curve.
    /// </summary>
    /// <param name="id">unique id for the curve, i.e. "Catenary"</param>
    /// <returns></returns>
    public CurveData AddCurve(Func<float, float> functionToPlot, string id) {
        if (curves.ContainsKey(id)) {
            if (curves[id] == null) curves.Remove(id);
            else {
                return curves[id];
            }
        }
        var c = Instantiate(curveDataPrefab, transform);
        var lr = Instantiate(lrPrefab, c.transform);
        lr.transform.parent = c.transform;
        c.lineRenderers.Add(lr);
        c.plot = this;
        c.setDataPoints(functionToPlot);
        curves.Add(id, c);
        return c;
    }
    public CurveData AddCurve(List<int> dataPoints, string id) {
        if (curves.ContainsKey(id)) {
            if (curves[id] == null) curves.Remove(id);
            else {
                return curves[id];
            }
        }
        var c = Instantiate(curveDataPrefab, transform);
        for (int i = 0; i < dataPoints.Count - 1; i++) {
            var lr = Instantiate(lrPrefab, c.transform);
            lr.transform.localScale = Vector3.one;
            lr.transform.localPosition = Vector3.zero;
            c.lineRenderers.Add(lr);
        }
        c.plot = this;
        c.setDataPoints(dataPoints);
        curves.Add(id, c);
        return c;
    }

    /// <summary>
    /// Removes a curve with the given id, if it exists.
    /// </summary>
    /// <param name="id">Id of the curve to remove</param>
    /// <returns>Returns true if succesfully removed the curve</returns>
    public bool RemoveCurve(string id) {
        return removeIfExists(id, curves);
    }

    public SurfaceData AddSurface(Func<float, float, float> functionToPlot, string id, bool remakeMesh = false, int edgeResolution = 21) {
        if (surfaces.ContainsKey(id)) {
            if (surfaces[id] == null) surfaces.Remove(id);
            else {
                return surfaces[id];
            }
        }
        var s = Instantiate(surfaceDataPrefab, transform);
        s.plot = this;
        s.mins = new Vector3 (xMin, yMin, zMin);
        s.maxs = new Vector3 (xMax, yMax, zMax);
        s.SetFunction(functionToPlot);
        surfaces.Add(id, s);
        return s;
    }

    public bool RemoveSurface(string id) {
        return removeIfExists(id, surfaces);
    }

    public StackedAreaData AddStackedArea(string id = "None", int pointsPerUnit = 1) {
        if (id == "None") {id = System.Environment.TickCount.ToString();}
        if (stackedAreas.ContainsKey(id)) {
            if (stackedAreas[id] == null) stackedAreas.Remove(id);
            else {
                return stackedAreas[id];
            }
        }
        var s = Instantiate(stackedAreaDataPrefab, transform);
        s.plot = this;
        s.mins = new Vector3 (xMin, yMin, zMin);
        s.maxs = new Vector3 (xMax, yMax, zMax);
        s.pointsPerUnit = pointsPerUnit;
        stackedAreas.Add(id, s);
        //Set this when added because updating clipping number doesn't set y.
        s.RefreshData();
        s.UpdateVisibleRange(s.mins, s.maxs); 
        return s;
    }
    public StackedAreaData AddStackedArea(List<float> func1, List<float> func2, List<float> func3, List<float> func4, string id = "None", int pointsPerUnit = 1) {
        var s = AddStackedArea(id, pointsPerUnit);
        s.SetFunctions(func1, func2, func3, func4);
        return s;
    }
    public StackedAreaData AddStackedArea(List<float> func1, List<float> func2, List<float> func3, string id = "None", int pointsPerUnit = 1) {
        var s = AddStackedArea(id, pointsPerUnit);
        s.SetFunctions(func1, func2, func3);
        return s;
    }
    public StackedAreaData AddStackedArea(List<float> func1, List<float> func2, string id = "None", int pointsPerUnit = 1) {
        var s = AddStackedArea(id, pointsPerUnit);
        s.SetFunctions(func1, func2);
        return s;
    }
    public StackedAreaData AddStackedArea(List<float> func1, string id = "None", int pointsPerUnit = 1) {
        var s = AddStackedArea(id, pointsPerUnit);
        s.SetFunctions(func1);
        return s;
    }

    public bool RemoveStackedArea(string id) {
        return removeIfExists(id, stackedAreas);
    }

    private bool removeIfExists<T> (string id, Dictionary<string, T> fromDictionary) where T : MonoBehaviour {
        if (fromDictionary.ContainsKey(id)) {
            var p = fromDictionary[id];
            if (p != null) Destroy(p.gameObject);
            fromDictionary.Remove(id);
            return true;
        }
        return false;
    }

    public void ChangeRangeY(float newMin, float newMax, float duration = 0.5f, EaseMode ease = EaseMode.Cubic) {
        StartCoroutine(changeRangeY(newMin, newMax, duration, ease));
    }

    private IEnumerator changeRangeY(float newMin, float newMax, float duration, EaseMode ease) {
        float oldMin = this.yMin;
        float oldMax = this.yMax;
        //TODO: Make this work for non-zero mins by changing axis offset and rodcontainer
        float startTime = Time.time;
        while (Time.time <= startTime + duration) {
            float t = (Time.time - startTime) / duration;
            t = Helpers.ApplyNormalizedEasing(t, ease);
            this.yMin = Mathf.Lerp(oldMin, newMin, t);
            this.yMax = Mathf.Lerp(oldMax, newMax, t);
            yield return null;
        }
        this.yMin = newMin;
        this.yMax = newMax;
        updateXRangeProperties();
    }
    private void updateYRangeProperties() {
        foreach (Tic tic in axesHandler.yTics) {
            tic.SetPosition();
        }
        axesHandler.HandleTicsY();
        if (labelsFaceCamera) {
            UpdateLabelList();//Definitely a more efficient way to do this, but maybe it doesn't matter.
        }
        pointData.RefreshData();
        foreach(var id in curves.Keys) {
            curves[id].RefreshData();
        }
        foreach (var id in surfaces.Keys) {
            surfaces[id].RefreshData();
        }
    }

    public void ChangeRangeX(float newMin, float newMax, float duration = 0.5f, EaseMode ease = EaseMode.Cubic) {
        StartCoroutine(changeRangeX(newMin, newMax, duration, ease));
    }

    private IEnumerator changeRangeX(float newMin, float newMax, float duration, EaseMode ease) {
        float oldMin = this.xMin;
        float oldMax = this.xMax;
        //TODO: Make this work for non-zero mins by changing axis offset and rodcontainer
        float startTime = Time.time;
        while (Time.time <= startTime + duration) {
            float t = (Time.time - startTime) / duration;
            t = Helpers.ApplyNormalizedEasing(t, ease);
            this.xMin = Mathf.Lerp(oldMin, newMin, t);
            this.xMax = Mathf.Lerp(oldMax, newMax, t);
            yield return null;
            updateXRangeProperties();

        }
        this.xMin = newMin;
        this.xMax = newMax;
        updateXRangeProperties();
    }

    private void updateXRangeProperties() {
        foreach (Tic tic in axesHandler.xTics) {
            tic.SetPosition();
        }
        axesHandler.HandleTicsX();
        if (labelsFaceCamera) {
            UpdateLabelList();//Definitely a more efficient way to do this, but maybe it doesn't matter.
        }
        pointData.RefreshData();
        foreach(var id in curves.Keys) {
            curves[id].RefreshData();
        }
        foreach (var id in surfaces.Keys) {
            surfaces[id].RefreshData();
        }
        foreach (var id in stackedAreas.Keys) {
            var s = stackedAreas[id];
            s.ScaleMesh();
        }
    }
        
    public Vector3 CoordinateToPosition(Vector3 graphSpaceCoords) {
        Vector3 newPosOfChild = new Vector3 (
            graphSpaceCoords.x * xLengthMinusPadding / (xMax - xMin),
            graphSpaceCoords.y * yLengthMinusPadding / (yMax - yMin),
            graphSpaceCoords.z * zLengthMinusPadding / (zMax - zMin)
        );
        return newPosOfChild;
    }
    public Vector3 CoordinateToPosition(float x, float y, float z) {
        return CoordinateToPosition(new Vector3(x, y, z));
    }

    public void SetLabelFacing(bool facing = true) {
        labelsFaceCamera = facing;
        if (facing) {
            UpdateLabelList();
        }
    }

    private void UpdateLabelList() {
        allLabels = new List<PrimerObject>();

        allLabels.AddRange(axesHandler.xTics);
        allLabels.AddRange(axesHandler.yTics);
        allLabels.AddRange(axesHandler.zTics);
        allLabels.Add(axesHandler.xAxisLabel);
        allLabels.Add(axesHandler.yAxisLabel);
        allLabels.Add(axesHandler.zAxisLabel);
    }

    protected override IEnumerator scaleTo(Vector3 newScale, float duration, EaseMode ease) {
        Vector3 initialScale = transform.localScale;
        
        //Assume scale uniform, which should always be the case for graphs
        float scaleFactor = (float) newScale.x / initialScale.x;
        Dictionary<string, float> initialWidths = new Dictionary<string, float>();
        foreach (KeyValuePair<string, CurveData> entry in curves) {
            //Assumes all linerenderers in a curve are the same width
            initialWidths.Add(entry.Key, entry.Value.lineRenderers[0].widthMultiplier);
        }
        
        float startTime = Time.time;
        while (Time.time < startTime + duration)
        {
            float t = (Time.time - startTime) / duration;
            t = Helpers.ApplyNormalizedEasing(t, ease);
            transform.localScale = Vector3.Lerp(initialScale, newScale, t);
            foreach (KeyValuePair<string, CurveData> entry in curves) {
                foreach (LineRenderer lr in entry.Value.lineRenderers) {
                    lr.widthMultiplier = Mathf.Lerp(initialWidths[entry.Key], initialWidths[entry.Key] * scaleFactor, t);
                }
            }
            yield return null;
        }

        transform.localScale = newScale; //Ensure we actually get exactly to newScale 
    }
}
