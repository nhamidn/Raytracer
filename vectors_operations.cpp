#include "raytracer.h"

//Function that calculate the reflected vector of a vector
vector3 Vectorreflect(vector3& incident, vector3& normal) {
	long double d = dotProduct(incident, normal);
	vector3 mul = vectorMultiply(normal, 2.0L * d);
	vector3 reflection = vectorSubtraction(incident, mul);
	return (normalize(reflection));
}

//Function that calculate the length of a vector
long double VectorLength(vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

long double cosineAngle(vector3& v1, vector3& v2) {
	// Normalize the vectors
	vector3 normalizedV1 = normalize(v1);
	vector3 normalizedV2 = normalize(v2);

	// Calculate the dot product
	long double dotProductValue = dotProduct(normalizedV1, normalizedV2);

	return dotProductValue;
}


//Function that sums two vectors
vector3 vectorSum(vector3& v1, vector3& v2) {
	vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

//Function that multiply a vector bye a value
vector3 vectorMultiply(vector3& v, long double value) {
	vector3 result;
	result.x = v.x * value;
	result.y = v.y * value;
	result.z = v.z * value;
	return result;
}

//Function that normalize a vector to the length of 1
vector3 normalize(vector3& vec) {
	long double length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length != 0) {
		vector3 newvec;
		newvec.x = vec.x / length;
		newvec.y = vec.y / length;
		newvec.z = vec.z / length;
		return (newvec);
	} else {
		return (vec);
	}
}

//Function that substract two vectors
vector3 vectorSubtraction(vector3& v1, vector3& v2) {
	vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

//Function that calculate the dotproduct of two vectors
long double dotProduct(vector3& v1, vector3& v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//Function that calculate the dotproduct of two vectors usin Theta
long double dotProductTheta(vector3& v1, vector3& v2, long double theta) {
	long double magnitude1 = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	long double magnitude2 = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	long double cosTheta = cos(theta);
	return (magnitude1 * magnitude2 * cosTheta);
}

//Function that calculate the angle between two vectors
long double calculateTheta(vector3& v1, vector3& v2) {
	long double dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	long double magnitude1 = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	long double magnitude2 = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);

	if (magnitude1 > 0 && magnitude2 > 0) {
		long double cosTheta = dotProduct / (magnitude1 * magnitude2);

		long double theta = acos(cosTheta);
		return theta;
	} else {
		return 0.0;
	}
}

