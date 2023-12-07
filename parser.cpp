#include "raytracer.h"

bool parseDouble(std::ifstream& file, long double& result) {
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);
		std::string token;
		stream >> token;

		std::cerr << token << std::endl;
		long double value;
		if (stream >> value) {
			result = value;
			return (true);
		} else {
			std::cerr << "Error parsing double." << std::endl;
			return (false);
		}
	}

	std::cerr << "Double not found in the file." << std::endl;
	return (false);
}

bool parseVector3(std::ifstream& file, vector3& result) {
	std::string line;
	if (std::getline(file, line)) {
		std::istringstream stream(line);
		std::string token;
		stream >> token;

		long double x, y, z;
		if (stream >> x >> y >> z) {
			result.x = x;
			result.y = y;
			result.z = z;
			return (true);
		} else {
			std::cerr << "Error parsing vector." << std::endl;
			return (false);
		}
	}

	return (false);
}

bool parseColorVector(std::ifstream& file, std::vector<int>& result) {
	std::string line;
	if (std::getline(file, line)) {
		std::istringstream stream(line);
		std::string token;
		stream >> token;

		int x, y, z;
		if (stream >> x >> y >> z) {
			result = {x, y, z};
			return (true);
		} else {
			std::cerr << "Error parsing color vector." << std::endl;
			return (false);
		}
	}

	return (false);
}

bool parseObjectParameters(std::ifstream& file, ObjectType objectType, RayObject& obj) {
	vector3 position, normal;
	std::vector<int> color;
	if (objectType == SPHERE) {
		long double radius;
		if (parseVector3(file, position) && parseVector3(file, normal)
				&& parseDouble(file, radius) && parseColorVector(file, color)) {
			obj.setPosition(position.x, position.y, position.z);
			obj.setNormal(normal.x, normal.y, normal.z);
			obj.setColor(color[0], color[1], color[2]);
			obj.setRadius(radius);
			return (0);
		}

	} else if (objectType == PLANE) {
		return (0);
	}

	return (1);
}

int parseLightParameters(std::ifstream& file, Light& newLight) {
        vector3 position;

        if (parseVector3(file, position)) {
                newLight.setPosition(position.x, position.y, position.z);
                return (0);
        }

        return (1);
}

//Function 
int parseCameraParameters(std::ifstream& file, Camera& newCamera) {
	vector3 position, lookAt;

	if (parseVector3(file, position) &&
			parseVector3(file, lookAt)) {
		newCamera.setPosition(position.x, position.y, position.z);
		newCamera.setlookAt(lookAt.x, lookAt.y, lookAt.z);
		return (0);
	}

	return (1);
}

//Function that parse the file
int parse_file(const std::string& filename, Scene& scene) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return (1);
	}

	std::string line;
	ObjectType currentObjectType = SPHERE;

	//We read line by line
	while (std::getline(file, line)) {
		std::istringstream stream(line);
		std::string token;
		stream >> token;
		//if the line start with camera, we parse the camera parameters
		if (token == "camera")
		{
			Camera newCamera;
			if (parseCameraParameters(file, newCamera) == 0) {
				scene.setCamera(newCamera);
			} else {
				std::cerr << "Error parsing camera parameters." << std::endl;
				return (1);
			}
		//if the line start with light, we parse the light parameters
		} else if (token == "light"){
			Light newLight;
			if (parseLightParameters(file, newLight) == 0) {
				scene.setLight(newLight);
				scene.addLight(newLight);
			} else {
				std::cerr << "Error parsing Light parameters." << std::endl;
				return (1);
			}
		//if the line start with an object type, we parse the object parameters
		} else if (token == "sphere") {
			currentObjectType = SPHERE;
			RayObject obj(currentObjectType);
			if (parseObjectParameters(file, currentObjectType, obj) == 0) {
				scene.addObject(obj);
			} else {
				std::cerr << "Error parsing sphere parameters." << std::endl;
				return (1);
			}
		}
	}

	file.close();

	return (0);
}

