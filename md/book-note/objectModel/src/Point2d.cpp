class Point2d{
	public:
		// ... 有
	protected:
		float _x, _y;
};

class Point3d : public Point2d{
	public:
		// ... 有
	protected:
		float _z;
};

class Vertex{
	public:
	protected:
		Vertex *next;
};

class Vertex3d : 
	public Point3, public Vertex{
	public:
	protected:
		float mumble;
};
