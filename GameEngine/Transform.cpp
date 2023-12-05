#include "Transform.h"

Transform::Transform() {
	position = Vector2(0, 0);
	scale = Vector2(1, 1);
}

Transform::Transform(Vector2 initialPosition) {
	position = initialPosition;
	scale = Vector2(1, 1);
}

Transform::Transform(Vector2 initialPosition, Vector2 initialScale) {
	position = initialPosition;
	scale = initialScale;
}
