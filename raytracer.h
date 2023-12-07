#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//
struct vector3 {
	long double x;
	long double y;
	long double z;
};

enum ObjectType {
	SPHERE,
	PLANE,
};

//Class prepresenting a Light
class Light {

	public:
		Light() {
		}
		void setPosition(long double x, long double y, long double z) {
			position.x = x;
			position.y = y;
			position.z = z;
		}
		vector3 getPosition() {
			return (position);
		}
	private:
		vector3 position;
		/* long double luminosity;*/
};

//Class prepresenting a camera
class Camera {
	public:
		Camera() {
		}

		void setPosition(long double x, long double y, long double z) {
			position.x = x;
			position.y = y;
			position.z = z;
		}
		void setlookAt(long double x, long double y, long double z) {
			lookAt.x = x;
			lookAt.y = y;
			lookAt.z = z;
		}
		void setUp(long double x, long double y, long double z) {
			up.x = x;
			up.y = y;
			up.z = z;
		}
		vector3 getPosition() {
			return (position);
		}
		vector3 getlookAt() {
			return (lookAt);
		}
	private:
		vector3 position;
		vector3 lookAt;
		vector3 up;
};

//Class prepresenting an object in the scene
class RayObject {
	public:
		RayObject(ObjectType objtype) : color({255, 255, 255}) {
			type = objtype;
		}
		void setPosition(long double x, long double y, long double z) {
			position.x = x;
			position.y = y;
			position.z = z;
		}
		void setNormal(long double x, long double y, long double z) {
			normal.x = x;
			normal.y = y;
			normal.z = z;
		}
		void setColor(int r, int g, int b) {
        		color = {r, g, b};
    		}
		void setRadius(long double s_radius) {
			radius = s_radius;
		}
		ObjectType getType() {
			return (type);
		}
		vector3 getPosition() {
			return (position);
		}
		vector3 getNormal() {
			return (normal);
		}
		std::vector<int> getColor() const {
        		return color;
    		}
		long double getRadius() {
			return (radius);
		}

	private:
		ObjectType type;
		vector3 position;
		vector3 normal;
		std::vector<int> color;
		long double radius;
};

//Scene class that groups all the elements of the scene
class Scene {
	public:
		Scene() {
		}
		void setCamera(const Camera& newCamera) {
			camera = newCamera;
		}
		void setLight(const Light& newLight) {
			light = newLight;
		}
		void addLight(const Light& light) {
			lights.push_back(light);
		}
		void addObject(const RayObject& object) {
			objects.push_back(object);
		}
		Camera getCamera() {
			return (camera);
		}
		Light getLight() {
			return (light);
		}
		std::vector<Light> getLights() {
        		return (lights);
		}

		std::vector<RayObject> getObjects() {
			return (objects);
		}

	private:
		Camera camera;
		Light light;
		std::vector<Light> lights;
		std::vector<RayObject> objects;
};

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;

} SDL_Instance;

int init_instance(SDL_Instance *);
int parse_file(const std::string& filename, Scene& scene);
void raytracer(SDL_Instance *instance, Scene& scene);
long double VectorLength(vector3& v);
long double cosineAngle(vector3& v1, vector3& v2);
vector3 vectorSum(vector3& v1, vector3& v2);
vector3 vectorMultiply(vector3& v, long double value);
vector3 normalize(vector3& vec);
vector3 vectorSubtraction(vector3& v1, vector3& v2);
long double dotProduct(vector3& v1, vector3& v2);
long double dotProductTheta(vector3& v1, vector3& v2, long double theta);
long double calculateTheta(vector3& v1, vector3& v2);
vector3 Vectorreflect(vector3& incident, vector3& normal);

#endif
