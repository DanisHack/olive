/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#include "viewer.h"

ViewerOutput::ViewerOutput()
{
  texture_input_ = new NodeInput("tex_out");
  texture_input_->add_data_input(NodeInput::kTexture);
  AddParameter(texture_input_);
}

QString ViewerOutput::Name()
{
  return tr("Viewer");
}

QString ViewerOutput::id()
{
  return "org.olivevideoeditor.Olive.vieweroutput";
}

QString ViewerOutput::Category()
{
  return tr("Output");
}

QString ViewerOutput::Description()
{
  return tr("Interface between a Viewer panel and the node system.");
}

const rational &ViewerOutput::Timebase()
{
  return timebase_;
}

void ViewerOutput::SetTimebase(const rational &timebase)
{
  timebase_ = timebase;

  emit TimebaseChanged(timebase_);
}

NodeInput *ViewerOutput::texture_input()
{
  return texture_input_;
}

RenderTexturePtr ViewerOutput::GetTexture(const rational &time)
{
  return texture_input_->get_value(time).value<RenderTexturePtr>();
}

void ViewerOutput::InvalidateCache(const rational &start_range, const rational &end_range, NodeInput *from)
{
  Node::InvalidateCache(start_range, end_range, from);

  emit TextureChangedBetween(start_range, end_range);

  SendInvalidateCache(start_range, end_range);
}

QVariant ViewerOutput::Value(NodeOutput *output, const rational &time)
{
  Q_UNUSED(output)
  Q_UNUSED(time)

  return 0;
}
