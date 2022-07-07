class RenderBehaviour
{
public:
	RenderBehaviour(){}
	virtual ~RenderBehaviour(){}

	virtual void OnUpdate() {}
	virtual void OnRender(){}
	virtual void OnImGUIRender(){}
};