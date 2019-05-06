#ifndef FM_RVIZ_POLYGON_TOOL_POLYGON_TOOL_H_
#define FM_RVIZ_POLYGON_TOOL_POLYGON_TOOL_H_

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreSceneNode.h>

#include <ros/console.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include <OgreVector3.h>
#include <OgreColourValue.h>
#include <rviz/geometry.h>
#include <rviz/ogre_helpers/line.h>
#include <rviz/ogre_helpers/shape.h>
#include <rviz/properties/vector_property.h>
#include <rviz/tool.h>
#include <rviz/render_panel.h>
#include <rviz/viewport_mouse_event.h>
#include <rviz/visualization_manager.h>

namespace mav_polygon_tool {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef Polygon_2::Vertex_iterator VertexIterator;

// Declare polygon tool as subclass of rviz::Tool.
class PolygonTool : public rviz::Tool {
  Q_OBJECT

public:
  PolygonTool();
  virtual ~PolygonTool();

  void onInitialize() override;

  void activate() override;
  void deactivate() override;
  int processKeyEvent(QKeyEvent *event, rviz::RenderPanel *pane) override;
  int processMouseEvent(rviz::ViewportMouseEvent &event) override;

  void load(const rviz::Config &config) override;
  void save(rviz::Config config) const override;
  std::vector<Polygon_2> getPolygon();

protected:
  void makeVertex(const Ogre::Vector3 &position);
  void leftClicked(rviz::ViewportMouseEvent &event);
  void rightClicked(rviz::ViewportMouseEvent &event);
  void drawLines();
  void checkCGalPolygon();

  std::vector<std::vector<rviz::Shape *>> active_spheres_;
  std::vector<std::vector<Ogre::SceneNode *>> vertex_nodes_;
  Ogre::SceneNode *moving_vertex_node_;
  rviz::VectorProperty *current_vertex_property_;
  std::vector<std::vector<rviz::Line *>> active_lines_;
  std::vector<std::list<Point>> points_for_poly_;

  std::vector<Polygon_2> polygon_;
  // Point display.
  rviz::Shape *vertex_;
  rviz::Shape *vertex2_;

  // point scale
  const float kPtScale = 0.5;
  const float kDeleteTol = 0.2;

private:
  Ogre::ColourValue red_, blue_, pink_, green_;
  void pushBackElements();
  void setColor(const Ogre::ColourValue &line_color, const Ogre::ColourValue &sphere_color);
  int current_polygon_ = 0;
  int current_type_;
  std::vector<int> type_of_polygons_;
  bool mouse_down_ = false;
};

} // namespace mav_polygon_tool

#endif // FM_RVIZ_POLYGON_TOOL_POLYGON_TOOL_H_
