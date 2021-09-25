#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main(void)
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(500, 300), "SFML Works!", Style::Default, settings);

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}
		// ������ ���� ����
		window.clear(Color(250, 220, 100, 0));

		// Texture
		// Work with textures ���� �� ����
		Image img;
		img.loadFromFile("C:\\Users\\New\\source\\repos\\Project1\\Debug\\transparent-paper-texture-5.png");

		Texture texture;
		texture.loadFromImage(img);
		texture.setSmooth(true);

		/*Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(50, 40);*/

		// Sprite
		Sprite sprite(texture);
		sprite.setColor(Color::Green);

		window.draw(sprite);

		// ������� ����
		CircleShape circle(50.f);
		circle.setFillColor(Color(230, 0, 230));
		circle.setOutlineThickness(10.f);
		circle.setOutlineColor(Color::Black);

		circle.move(50, 50);

		circle.setTexture(&texture);

		window.draw(circle);

		// ������ �����������
		CircleShape triangle(50.f, 3);
		triangle.setPosition(170, 50);
		triangle.setFillColor(Color::Cyan);

		window.draw(triangle);

		// Creating convex shape (�������� �������������)
		ConvexShape convex;

		convex.setPointCount(5);

		convex.setPoint(0, Vector2f(15.f, 15.f));
		convex.setPoint(1, Vector2f(150.f, 10.f));
		convex.setPoint(2, Vector2f(120.f, 90.f));
		convex.setPoint(3, Vector2f(30.f, 100.f));
		convex.setPoint(4, Vector2f(5.f, 50.f));

		convex.setFillColor(Color::Black);

		convex.move(150, 150);

		window.draw(convex);

		//Creating rectangle
		RectangleShape rectangle(Vector2f(70.f, 100.f));

		rectangle.move(165, 150);
		rectangle.rotate(45);

		rectangle.setFillColor(Color(175, 180, 240));

		window.draw(rectangle);

		// Creating zero-width line via VertexArray
		VertexArray line(Lines, 2);

		line[0].position = Vector2f(300.f, 220.f);
		line[1].position = Vector2f(420.f, 90.f);

		line[0].color = Color::Black;
		line[1].color = Color::Magenta;


		window.draw(line);

		// Creating zero-width line
		Vertex zero_widthLine[]
		{
			Vertex(Vector2f(390.f, 240.f)),
			Vertex(Vector2f(470.f, 150.f))
		};
		zero_widthLine->color = Color::Black;

		window.draw(zero_widthLine, 2, Lines);

		// Creating Triangle via VertexArray
		VertexArray triangle_v(Triangles, 3);
		
		triangle_v[0].position = Vector2f(250.f, 80.f);
		triangle_v[1].position = Vector2f(200.f, 150.f);
		triangle_v[2].position = Vector2f(350.f, 130.f);

		triangle_v[0].color = Color::Cyan;
		triangle_v[1].color = Color::Red;
		triangle_v[2].color = Color::Green;

		window.draw(triangle_v);

		// ��������� ����	
		window.display();
	}
	return 0;
}