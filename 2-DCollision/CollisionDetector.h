#ifndef COLLISION_DETECTOR
#define COLLISION_DETECTOR



namespace cd
{
#define PI 3.141592653
	struct Vector
	{
		float x;
		float y;
	};

	struct Rotation
	{
		float cos;
		float sin;
	};

	struct Quad
	{
		Vector topLeft;
		Vector size;
		Rotation rotation;
	};


}

#endif