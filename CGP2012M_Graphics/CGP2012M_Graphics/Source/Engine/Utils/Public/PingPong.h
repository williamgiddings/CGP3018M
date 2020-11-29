#pragma once


class PingPong
{

public:

	PingPong( float Min, float Max )
		: Value( 0.0f )
		, Min( Min )
		, Max( Max )
		, Dir( 1 )

	{};

public:

	float Advance( float Speed )
	{
		Value += Speed * Dir;
		if ( Value > Max )
		{
			Value = Max;
			Dir = -1;
		}
		else if ( Value < Min )
		{
			Value = Min;
			Dir = 1;
		}
		return Value;
	}

private:

	float Value;
	float Min;
	float Max;

	int Dir;
};