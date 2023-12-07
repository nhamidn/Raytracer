#include "raytracer.h"

// Function that gets the minimum of two values
long double ft_min_posi(long double t1, long double t2)
{
	if (t1 < t2)
	{
		if (t1 > 0)
			return (t1);
		else
			return (t2);
	}
	else if (t1 > t2)
	{
		if (t2 > 0)
			return (t2);
		else
			return (t1);
	}
	return (6000.0);
}

//Function that solves the quadratic equation
long double solveQuadratic(long double &a, long double &b, long double &c)
{
	long double x0, x1;
	long double discr = b * b - (4 * a * c);
	if (discr < 0) return (6000.0);

	x0 = (-b + sqrtf(discr)) / (2 * a);
	x1 = (-b - sqrtf(discr)) / (2 * a);

	if ((x0 < 0 && x1 < 0))
		return (6000.0);

	return (ft_min_posi(x0, x1));
}

//Function that check if a ray intersect with a given sphere
long double checkIntersectionSphere(RayObject& sphere, Scene& scene, vector3& ray) {
	vector3 cameraPosition = scene.getCamera().getPosition();
	vector3 spherePosition = sphere.getPosition();

	vector3 L = vectorSubtraction(cameraPosition, spherePosition);
	long double a = dotProduct(ray, ray);// = 1.0
	long double b = 2 * dotProduct(ray, L);
	long double c = dotProduct(L, L) - (sphere.getRadius() * sphere.getRadius());
	return (solveQuadratic(a, b, c));
}


//Function that send on every object in the scene
size_t sendRay(Scene& scene, vector3& ray, long double& dist) {
	long double limit = 5000.0;
	long double min_dist = 6000.0;
	size_t objIndex = std::numeric_limits<size_t>::max();
	std::vector<RayObject> objects = scene.getObjects();

	// We loop over the objects of the scene
	for (size_t i = 0; i < objects.size(); ++i) {
		long double distance = 6000.0;
		if (objects[i].getType() == SPHERE) {
			//We get the distance between the origin and the sphere intersection point
			distance = checkIntersectionSphere(objects[i], scene, ray);
		} else if (objects[i].getType() == PLANE) {
			// Handle plane intersection if needed
		}

		//If the distance if positive and less that 6000 and less that the previous intersection
		//we save the new intersected object
		if (distance < min_dist && distance > 0 && distance < limit) {
			objIndex = i;
			min_dist = distance;
		}
	}
	dist = min_dist;
	return (objIndex);
}

void raytracer(SDL_Instance *instance, Scene& scene)
{
	SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);

	vector3 camPos = scene.getCamera().getPosition();
	vector3 camdir = scene.getCamera().getlookAt();
	camdir = normalize(camdir);
	//long double screenDistance = 1.0;
	long double screenWidth = 1.0;
	long double screenHeight = 1.0;

	//Looping over the windows pixels
	for (int j = 0; j < 800; j++) {
		for (int i = 0; i < 800; i++) {
			//Mapping the windows pixels indexes
			long double pixelX = screenWidth * (i / 800.0 - 0.5);
			long double pixelY = screenHeight * (0.5 - j / 800.0);
			//long double pixelY = screenHeight * (j / 800.0 - 0.5);

			long double distance;

			//We set the ray direction and normalize it
			vector3 rayDir;
			rayDir = camdir;
			rayDir.x += pixelX;
			rayDir.y += pixelY;
			rayDir = normalize(rayDir);

			//We check if the ray intersect with any object
			size_t objIndex = sendRay(scene, rayDir, distance);

			//If the ray intersect with any object, we calculate the lighting if the object
			if (objIndex != std::numeric_limits<size_t>::max()) {
				RayObject obj = scene.getObjects()[objIndex];
				//We calculate the intersection coordinate using the distance we got
				vector3 intersection_vector = vectorMultiply(rayDir, distance);
				vector3 intersection_point = vectorSum(camPos, intersection_vector);
				vector3 objPos = obj.getPosition();
				long double ambientIntensity = 0.2;
				long double Intensity = 0.0;
				//long double specularIntensity = 0.0;
				//long double specularCosAngle = 0.0;
				std::vector<Light> lights = scene.getLights();
				if (obj.getType() == SPHERE) {
					vector3 normal = vectorSubtraction(intersection_point, objPos);
					for (size_t l = 0; l < lights.size(); ++l) {
						vector3 light_pos = lights[l].getPosition();
						vector3 lightDirection = vectorSubtraction(light_pos, intersection_point);
						//we calculate the angle between the normal of the sphere
						//and the direction from the intersection point to the light position
						long double cosAngle = cosineAngle(normal, lightDirection);
						Intensity += std::max(cosAngle, static_cast<long double>(0.0));

						// Specular reflection
						/*vector3 inter_cam = vectorMultiply(rayDir, -1.0);
						vector3 viewDirection = normalize(inter_cam);
						vector3 reflectionDirection = Vectorreflect(lightDirection, normal);
						specularCosAngle = std::max(cosineAngle(reflectionDirection, viewDirection), static_cast<long double>(0.0));
						specularIntensity += pow(specularCosAngle, 1.0);*/
					}
				}
				Intensity += ambientIntensity;
				Intensity = Intensity > 1.0L ? 1.0 : Intensity;
				/*Intensity += specularIntensity;*/
				std::vector<int> color = obj.getColor();
				/*color[0] = color[0] * Intensity;
				if (color[0] > 255)
					color[0] = 255;
				color[1] = color[1] * Intensity;
				if (color[1] > 255)
        				color[1] = 255;
				color[2] = color[2] * Intensity;
				if (color[2] > 255)
        				color[2] = 255;*/
				SDL_SetRenderDrawColor(instance->renderer, color[0] * Intensity, color[1] * Intensity, color[2] * Intensity, 255);
				SDL_RenderDrawPoint(instance->renderer, i, j);
			}
			else {

			}
		}
	}
}
