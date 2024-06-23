#include <string>
#include "MyEnemy.hpp"

MyEnemy::MyEnemy(int x, int y) : Enemy("play/MyEnemy.png", x, y, 15, 50, 60, 200) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}