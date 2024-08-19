#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"

typedef struct {
	Vector3 *transformedPoints;
	Vector3 *notTransformed;
	int numPoints;
	Vector3 *normals;
	int numNormals;
} Collider;

void GetNormals(Mesh mesh, Vector3 *normals);
void SetupColliderMesh(Collider *c, Mesh mesh);
void GetMinMax(Collider b, Vector3 axis, float *min, float *max);
Vector3 GetMiddlePoint(Vector3 *vertices, int numVertices);
bool CheckCollision(Collider a, Collider b, Vector3 *normal);
void UpdateCollider(Vector3 parent, Collider *c);
void UnloadCollider(Collider *collider);

#endif
