#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.2

struct BuffEffect : IEffect
{

	struct BuffLine
	{
		Vec2 offset;
		double startTime;
		ColorF color;
		double width;
		double height;
	};

	const Vec2 m_pos;

	Array<BuffLine> m_bLine;

	Size sceneSize{ Scene::Size() };
	const RenderTexture gaussianA1{ sceneSize }, gaussianB1{ sceneSize };
	const RenderTexture gaussianA4{ sceneSize / 4 }, gaussianB4{ sceneSize / 4 };

	BuffEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		AudioAsset(U"GameSE0").play(MixBus1);
		for (int32 i = 0; i < 14; ++i)
		{
			BuffLine Bline{
				.offset = RandomVec2(Circle(34)),
				.startTime = Random(-0.2,0.2), // 登場の時間差
				.color = ColorF{HSV{ 100 + Random(-25,25)},Random(0.8,1.0)},
				.width = Random(2.0,4.0),
				.height = Random(15.0,20.0)

			};
			m_bLine << Bline;
		}

	}
	void draw(double t)
	{
		for (const auto& Bline : m_bLine)
		{
			const double t2 = (Bline.startTime + t);

			if (not InRange(t2, 0.0, 0.6))
			{
				continue;
			}

			const double t3 = (t2) * (1 / 0.6);
			const double eb = EaseInBack(t3);
			const double ee = EaseInQuint(t3);

			Line(m_pos + Bline.offset - Vec2(0, eb * 30), m_pos + Bline.offset + Vec2(0, Bline.height - eb * 20)).draw(Bline.width - (Bline.width * ee / 2), Bline.color);
		}
	}

	bool update(double t) override
	{
		draw(t);
		{
			const ScopedRenderTarget2D target{ gaussianA1.clear(ColorF{ 0.0 }) };
			const ScopedRenderStates2D blend{ BlendState::Additive };

			draw(t);
		}

		Shader::GaussianBlur(gaussianA1, gaussianB1, gaussianA1);
		Shader::Downsample(gaussianA1, gaussianA4);
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);

		{
			const ScopedRenderStates2D blend{ BlendState::Additive };
			gaussianA1.resized(sceneSize).draw(ColorF{ 0.1 });
			gaussianA4.resized(sceneSize).draw(ColorF{ 0.4 });
		}

		if (t >= 1.3)
		{
			AudioAsset(U"GameSE0").stop();
		}
		return (t < 1.3);
	}
};

struct DebuffEffect : IEffect
{
	struct BuffLine
	{
		Vec2 offset;
		double startTime;
		ColorF color;
		double width;
		double height;
	};

	const Vec2 m_pos;

	Array<BuffLine> m_bLine;

	Size sceneSize{ Scene::Size() };
	const RenderTexture gaussianA1{ sceneSize }, gaussianB1{ sceneSize };
	const RenderTexture gaussianA4{ sceneSize / 4 }, gaussianB4{ sceneSize / 4 };

	DebuffEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		//audio.setVolume(0.02);
		AudioAsset(U"GameSE2").play(MixBus1);
		for (int32 i = 0; i < 14; ++i)
		{
			BuffLine Bline{
				.offset = RandomVec2(Circle(34)),
				.startTime = Random(-0.2,0.2), // 登場の時間差
				.color = ColorF{HSV{ 335 + Random(-25,25)},Random(0.8,1.0)},
				.width = Random(2.0,4.0),
				.height = Random(15.0,20.0)

			};
			m_bLine << Bline;
		}

	}
	void draw(double t)
	{
		for (const auto& Bline : m_bLine)
		{
			const double t2 = (Bline.startTime + t);

			if (not InRange(t2, 0.0, 0.6))
			{
				continue;
			}

			const double t3 = (t2) * (1 / 0.6);
			const double eb = EaseInBack(t3);
			const double ee = EaseInQuint(t3);

			Line(m_pos + Bline.offset + Vec2(0, eb * 30), m_pos + Bline.offset - Vec2(0, Bline.height - eb * 20)).draw(Bline.width - (Bline.width * ee / 2), Bline.color);
		}
	}

	bool update(double t) override
	{
		draw(t);
		{
			const ScopedRenderTarget2D target{ gaussianA1.clear(ColorF{ 0.0 }) };
			const ScopedRenderStates2D blend{ BlendState::Additive };

			draw(t);
		}

		Shader::GaussianBlur(gaussianA1, gaussianB1, gaussianA1);
		Shader::Downsample(gaussianA1, gaussianA4);
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);

		{
			const ScopedRenderStates2D blend{ BlendState::Additive };
			gaussianA1.resized(sceneSize).draw(ColorF{ 0.1 });
			gaussianA4.resized(sceneSize).draw(ColorF{ 0.4 });
		}

		if (t >= 1.3)
		{
			AudioAsset(U"GameSE0").stop();
		}
		return (t < 1.3);
	}
};

struct SearchEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double startTime;
		double scale;
		ColorF color;
	};

	const Vec2 m_pos;

	Array<Bubble> m_bubbles;

	Size sceneSize{ Scene::Size() };
	const RenderTexture gaussianA1{ sceneSize }, gaussianB1{ sceneSize };
	const RenderTexture gaussianA4{ sceneSize / 4 }, gaussianB4{ sceneSize / 4 };

	SearchEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		//audio.setVolume(0.1);
		AudioAsset(U"GameSE1").play(MixBus1);
		for (int32 i = 0; i < 8; ++i)
		{
			Bubble bubble{
				.offset = RandomVec2(Circle{14}),
				.startTime = Random(-0.1, 0.1), // 登場の時間差
				.scale = Random(0.3, 0.6),
				.color = HSV{ 100 + Random(-30.0, 30.0) }
			};
			m_bubbles << bubble;
		}

	}
	void draw(double t)
	{
		Circle(m_pos, t * 1000).drawFrame(3, Palette::Orange);
		if (t >= 0.05)
			Circle(m_pos, (t - 0.05) * 1000).drawFrame(3, Palette::Orange);
	}

	bool update(double t) override
	{
		draw(t);
		{
			const ScopedRenderTarget2D target{ gaussianA1.clear(ColorF{ 0.0 }) };
			const ScopedRenderStates2D blend{ BlendState::Additive };

			draw(t);
		}

		Shader::GaussianBlur(gaussianA1, gaussianB1, gaussianA1);
		Shader::Downsample(gaussianA1, gaussianA4);
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);

		{
			const ScopedRenderStates2D blend{ BlendState::Additive };
			gaussianA1.resized(sceneSize).draw(ColorF{ 0.1 });
			gaussianA4.resized(sceneSize).draw(ColorF{ 0.4 });
		}

		if (t >= 2.0)
		{
			AudioAsset(U"GameSE2").stop();
		}
		return (t < 2.0);
	}
};
