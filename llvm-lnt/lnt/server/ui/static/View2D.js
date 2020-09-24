//===-- View2D.js - HTML5 Canvas Based 2D View/Graph Widget ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements a generic 2D view widget and a 2D graph widget on top of
// it, using the HTML5 Canvas. It currently supports Chrome, Firefox, and
// Safari.
//
// See the Graph2D implementation for details of how to extend the View2D
// object.
//
//===----------------------------------------------------------------------===//

function lerp(a, b, t) {
    return a * (1.0 - t) + b * t;
}

function clamp(a, lower, upper) {
    return Math.max(lower, Math.min(upper, a));
}

function vec2_neg (a)    { return [-a[0]    , -a[1]    ]; };
function vec2_add (a, b) { return [a[0]+b[0], a[1]+b[1]]; };
function vec2_addN(a, b) { return [a[0]+b   , a[1]+b   ]; };
function vec2_sub (a, b) { return [a[0]-b[0], a[1]-b[1]]; };
function vec2_subN(a, b) { return [a[0]-b   , a[1]-b   ]; };
function vec2_mul (a, b) { return [a[0]*b[0], a[1]*b[1]]; };
function vec2_mulN(a, b) { return [a[0]*b   , a[1]*b   ]; };
function vec2_div (a, b) { return [a[0]/b[0], a[1]/b[1]]; };
function vec2_divN(a, b) { return [a[0]/b   , a[1]/b   ]; };

function vec3_neg (a)    { return [-a[0]    , -a[1]    , -a[2]    ]; };
function vec3_add (a, b) { return [a[0]+b[0], a[1]+b[1], a[2]+b[2]]; };
function vec3_addN(a, b) { return [a[0]+b   , a[1]+b,    a[2]+b   ]; };
function vec3_sub (a, b) { return [a[0]-b[0], a[1]-b[1], a[2]-b[2]]; };
function vec3_subN(a, b) { return [a[0]-b   , a[1]-b,    a[2]-b   ]; };
function vec3_mul (a, b) { return [a[0]*b[0], a[1]*b[1], a[2]*b[2]]; };
function vec3_mulN(a, b) { return [a[0]*b   , a[1]*b,    a[2]*b   ]; };
function vec3_div (a, b) { return [a[0]/b[0], a[1]/b[1], a[2]/b[2]]; };
function vec3_divN(a, b) { return [a[0]/b   , a[1]/b,    a[2]/b   ]; };

function vec2_lerp(a, b, t) {
    return [lerp(a[0], b[0], t), lerp(a[1], b[1], t)];
}
function vec2_mag(a) {
    return a[0] * a[0] + a[1] * a[1];
}
function vec2_len(a) {
    return Math.sqrt(vec2_mag(a));
}

function vec2_floor(a) {
    return [Math.floor(a[0]), Math.floor(a[1])];
}
function vec2_ceil(a) {
    return [Math.ceil(a[0]), Math.ceil(a[1])];
}

function vec3_floor(a) {
    return [Math.floor(a[0]), Math.floor(a[1]), Math.floor(a[2])];
}
function vec3_ceil(a) {
    return [Math.ceil(a[0]), Math.ceil(a[1]), Math.ceil(a[2])];
}

function vec2_log(a) {
    return [Math.log(a[0]), Math.log(a[1])];
}
function vec2_pow(a, b) {
   return [Math.pow(a[0], b[0]), Math.pow(a[1], b[1])];
}
function vec2_Npow(a, b) {
   return [Math.pow(a, b[0]), Math.pow(a, b[1])];
}
function vec2_powN(a, b) {
   return [Math.pow(a[0], b), Math.pow(a[1], b)];
}

function vec2_min(a, b) {
    return [Math.min(a[0], b[0]), Math.min(a[1], b[1])];
}
function vec2_max(a, b) {
    return [Math.max(a[0], b[0]), Math.max(a[1], b[1])];
}
function vec2_clamp(a, lower, upper) {
    return [clamp(a[0], lower[0], upper[0]),
            clamp(a[1], lower[1], upper[1])];
}
function vec2_clampN(a, lower, upper) {
    return [clamp(a[0], lower, upper),
            clamp(a[1], lower, upper)];
}

function vec3_min(a, b) {
    return [Math.min(a[0], b[0]), Math.min(a[1], b[1]), Math.min(a[2], b[2])];
}
function vec3_max(a, b) {
    return [Math.max(a[0], b[0]), Math.max(a[1], b[1]), Math.max(a[2], b[2])];
}
function vec3_clamp(a, lower, upper) {
    return [clamp(a[0], lower[0], upper[0]),
            clamp(a[1], lower[1], upper[1]),
            clamp(a[2], lower[2], upper[2])];
}
function vec3_clampN(a, lower, upper) {
    return [clamp(a[0], lower, upper),
            clamp(a[1], lower, upper),
            clamp(a[2], lower, upper)];
}

function vec2_cswap(a, swap) {
    if (swap)
        return [a[1],a[0]];
    return a;
}

function col3_to_rgb(col) {
    var norm = vec3_floor(vec3_clampN(vec3_mulN(col, 255), 0, 255));
    return "rgb(" + norm[0] + "," + norm[1] + "," + norm[2] + ")";
}

function col4_to_rgba(col) {
    var norm = vec3_floor(vec3_clampN(vec3_mulN(col, 255), 0, 255));
    var result = "rgba(";
    result += norm[0] + ",";
    result += norm[1] + ",";
    result += norm[2] + ",";
    result += col[3] + ")";
    return result;
}

/* ViewData Class */

function ViewData(location, scale) {
    if (!location)
        location = [0, 0];
    if (!scale)
        scale = [1, 1];

    this.location = location;
    this.scale = scale;
}

ViewData.prototype.copy = function() {
    return new ViewData(this.location, this.scale);
};

/* ViewAction Class */
function ViewAction(mode, v2d, start) {
    this.mode = mode;
    this.start = start;
    this.vd = v2d.viewData.copy();
}

ViewAction.prototype.update = function(v2d, co) {
    if (this.mode == 'p') {
        var delta = vec2_sub(v2d.convertClientToNDC(co, this.vd),
            v2d.convertClientToNDC(this.start, this.vd));
        v2d.viewData.location = vec2_add(this.vd.location, delta);
    } else {
        var delta = vec2_sub(v2d.convertClientToNDC(co, this.vd),
            v2d.convertClientToNDC(this.start, this.vd));
        v2d.viewData.scale = vec2_Npow(Math.E,
                                       vec2_add(vec2_log(this.vd.scale),
                                                delta));
        v2d.viewData.location = vec2_mul(this.vd.location,
                                         vec2_div(v2d.viewData.scale,
                                                  this.vd.scale));
    }

    v2d.refresh();
};

ViewAction.prototype.complete = function(v2d, co) {
    this.update(v2d, co);
};

ViewAction.prototype.abort = function(v2d) {
    v2d.viewData = this.vd;
};

/* EventWrapper Class */

function EventWrapper(domevent) {
    this.domevent = domevent;
    this.client = {
        x: domevent.clientX,
        y: domevent.clientY
    };
    this.alt = domevent.altKey;
    this.shift = domevent.shiftKey;
    this.meta = domevent.metaKey;
    this.wheel = (domevent.wheelDelta) ? domevent.wheelDelta / 120 : -(domevent.detail || 0) / 3;
}

EventWrapper.prototype.stop = function() {
    this.domevent.stopPropagation();
    this.domevent.preventDefault();
};

/* View2D Class */

function View2D(canvasname)  {
    this.canvasname = canvasname;
    this.viewData = new ViewData();
    this.size = [1, 1];
    this.aspect = 1;
    this.registered = false;

    this.viewAction = null;

    this.useWidgets = true;
    this.previewPosition = [5, 5];
    this.previewSize = [60, 60];

    this.clearColor = [1, 1, 1];

    // Bound once registered.
    this.canvas = null;
}

View2D.prototype.registerEvents = function(canvas) {
    if (this.registered)
        return;

    this.registered = true;

    this.canvas = canvas;

    // FIXME: Why do I have to do this?
    var obj = this;

    canvas.onmousedown = function(event) { obj.onMouseDown(new EventWrapper(event)); };
    canvas.onmousemove = function(event) { obj.onMouseMove(new EventWrapper(event)); };
    canvas.onmouseup = function(event) { obj.onMouseUp(new EventWrapper(event)); };
    canvas.onmousewheel = function(event) { obj.onMouseWheel(new EventWrapper(event)); };
    if (canvas.addEventListener) {
        canvas.addEventListener('DOMMouseScroll', function(event) { obj.onMouseWheel(new EventWrapper(event)); }, false);
    }

    // FIXME: Capturing!
};

View2D.prototype.onMouseDown = function(event) {
    pos = [event.client.x - this.canvas.offsetLeft,
           this.size[1] - 1 - (event.client.y - this.canvas.offsetTop)];

    if (this.viewAction != null)
        this.viewAction.abort(this);

    if (event.shift)
        this.viewAction = new ViewAction('p', this, pos);
    else if (event.alt || event.meta)
        this.viewAction = new ViewAction('z', this, pos);
    event.stop();
};

View2D.prototype.onMouseMove = function(event) {
    pos = [event.client.x - this.canvas.offsetLeft,
           this.size[1] - 1 - (event.client.y - this.canvas.offsetTop)];

    if (this.viewAction != null)
        this.viewAction.update(this, pos);
    event.stop();
};

View2D.prototype.onMouseUp = function(event) {
    pos = [event.client.x - this.canvas.offsetLeft,
           this.size[1] - 1 - (event.client.y - this.canvas.offsetTop)];

    if (this.viewAction != null)
        this.viewAction.complete(this, pos);
    this.viewAction = null;
    event.stop();
};

View2D.prototype.onMouseWheel = function(event) {
    if (this.viewAction == null) {
        var factor = event.wheel;
        if (event.shift)
            factor *= .1;
        var zoom = 1.0 + .03 * factor;
        this.viewData.location = vec2_mulN(this.viewData.location, zoom);
        this.viewData.scale = vec2_mulN(this.viewData.scale, zoom);

        // Arbitrary limit min and max scales for now, ideally would be derived
        // based on the view contents.
        this.viewData.scale = vec2_clampN(this.viewData.scale, 10e-6, 10e6);

        this.refresh();
    }
    event.stop();
};

View2D.prototype.setViewData = function(vd) {
    // FIXME: Check equality and avoid refresh.
    this.viewData = vd;
    this.refresh();
};

View2D.prototype.refresh = function() {
    // FIXME: Event loop?
    this.draw();
};

// Coordinate conversion.

View2D.prototype.getAspectScale = function() {
    if (this.aspect > 1) {
        return [1.0 / this.aspect, 1.0];
    } else {
        return [1.0, this.aspect];
    }
};

View2D.prototype.getPixelSize = function() {
    return vec2_sub(this.convertClientToWorld([1,1]),
                    this.convertClientToWorld([0,0]));
};

View2D.prototype.convertClientToNDC = function(pt, vd) {
    if (vd == null)
        vd = this.viewData;
    return [pt[0] / this.size[0] * 2 - 1,
            pt[1] / this.size[1] * 2 - 1];
};

View2D.prototype.convertClientToWorld = function(pt, vd) {
    if (vd == null)
        vd = this.viewData;
    pt = this.convertClientToNDC(pt, vd);
    pt = vec2_sub(pt, vd.location);
    pt = vec2_div(pt, vec2_mul(vd.scale, this.getAspectScale()));
    return pt;
};

View2D.prototype.convertWorldToPreview = function(pt, pos, size) {
    var asp_scale = this.getAspectScale();
    pt = vec2_mul(pt, asp_scale);
    pt = vec2_addN(pt, 1);
    pt = vec2_mulN(pt, .5);
    pt = vec2_mul(pt, size);
    pt = vec2_add(pt, pos);
    return pt;
};

View2D.prototype.setViewMatrix = function(ctx) {
    ctx.scale(this.size[0], this.size[1]);
    ctx.scale(.5, .5);
    ctx.translate(1, 1);
    ctx.translate(this.viewData.location[0], this.viewData.location[1]);
    var scale = vec2_mul(this.viewData.scale, this.getAspectScale());
    ctx.scale(scale[0], scale[1]);
};

View2D.prototype.setPreviewMatrix = function(ctx, pos, size) {
    ctx.translate(pos[0], pos[1]);
    ctx.scale(size[0], size[1]);
    ctx.scale(.5, .5);
    ctx.translate(1, 1);
    var scale = this.getAspectScale();
    ctx.scale(scale[0], scale[1]);
};

View2D.prototype.setWindowMatrix = function(ctx) {
    ctx.translate(.5, .5);
    ctx.translate(0, this.size[1]);
    ctx.scale(1, -1);
};

View2D.prototype.draw = function() {
    var canvas = document.getElementById(this.canvasname);
    var ctx = canvas.getContext("2d");

    this.registerEvents(canvas);

    if (canvas.width != this.size[0] || canvas.height != this.size[1]) {
        this.size = [canvas.width, canvas.height];
        this.aspect = canvas.width / canvas.height;
        this.previewPosition[0] = this.size[0] - this.previewSize[0] - 5;
        this.on_size_change();
    }

    this.on_draw_start();

    ctx.save();

    // Clear and draw the view content.
    ctx.save();
    this.setWindowMatrix(ctx);

    ctx.clearRect(0, 0, this.size[0], this.size[1]);
    ctx.fillStyle = col3_to_rgb(this.clearColor);
    ctx.fillRect(0, 0, this.size[0], this.size[1]);

    this.setViewMatrix(ctx);
    this.on_draw(canvas, ctx);
    ctx.restore();

    if (this.useWidgets)
        this.drawPreview(canvas, ctx);

    ctx.restore();
};

View2D.prototype.drawPreview = function(canvas, ctx) {
    // Setup the preview context.
    this.setWindowMatrix(ctx);

    // Draw the preview area outline.
    ctx.fillStyle = "rgba(128,128,128,.5)";
    ctx.fillRect(this.previewPosition[0]-1, this.previewPosition[1]-1,
                 this.previewSize[0]+2, this.previewSize[1]+2);
    ctx.lineWidth = 1;
    ctx.strokeStyle = "rgb(0,0,0)";
    ctx.strokeRect(this.previewPosition[0]-1, this.previewPosition[1]-1,
                   this.previewSize[0]+2, this.previewSize[1]+2);

    // Compute the aspect corrected preview area.
    var pv_size = [this.previewSize[0], this.previewSize[1]];
    if (this.aspect > 1) {
        pv_size[1] /= this.aspect;
    } else {
        pv_size[0] *= this.aspect;
    }
    var pv_pos = vec2_add(this.previewPosition,
        vec2_mulN(vec2_sub(this.previewSize, pv_size), .5));

    // Draw the preview, making sure to clip to the proper area.
    ctx.save();
    ctx.beginPath();
    ctx.rect(pv_pos[0], pv_pos[1], pv_size[0], pv_size[1]);
    ctx.clip();
    ctx.closePath();

    this.setPreviewMatrix(ctx, pv_pos, pv_size);
    this.on_draw_preview(canvas, ctx);
    ctx.restore();

    // Draw the current view overlay.
    //
    // FIXME: Find a replacement for stippling.
    ll = this.convertClientToWorld([0, 0]);
    ur = this.convertClientToWorld(this.size);

    // Convert to pixel coordinates instead of drawing in content
    // perspective.
    ll = vec2_floor(this.convertWorldToPreview(ll, pv_pos, pv_size));
    ur = vec2_ceil(this.convertWorldToPreview(ur, pv_pos, pv_size));
    ll = vec2_clamp(ll, this.previewPosition,
                    vec2_add(this.previewPosition, this.previewSize));
    ur = vec2_clamp(ur, this.previewPosition,
                    vec2_add(this.previewPosition, this.previewSize));

    ctx.strokeStyle = "rgba(128,128,128,255)";
    ctx.lineWidth = 1;
    ctx.strokeRect(ll[0], ll[1], ur[0] - ll[0], ur[1] - ll[1]);
};

View2D.prototype.on_size_change = function() {};
View2D.prototype.on_draw_start = function() {};
View2D.prototype.on_draw = function(canvas, ctx) {};
View2D.prototype.on_draw_preview = function(canvas, ctx) {};

/* View2DTest Class */

function View2DTest(canvasname) {
    View2D.call(this, canvasname);
}
View2DTest.prototype = new View2D();
View2DTest.prototype.constructor = View2DTest;

View2DTest.prototype.on_draw = function(canvas, ctx) {
    ctx.fillStyle = "rgb(255,255,255)";
    ctx.fillRect(-1000, -1000, 2000, 20000);

    ctx.lineWidth = .01;
    ctx.strokeTyle = "rgb(0,200,0)";
    ctx.strokeRect(-1, -1, 2, 2);

    ctx.fillStyle = "rgb(200,0,0)";
    ctx.fillRect(-.8, -.8, 1, 1);

    ctx.fillStyle = "rgb(0,0,200)";
    ctx.beginPath();
    ctx.arc(0, 0, .5, 0, 2 * Math.PI, false);
    ctx.fill();
    ctx.closePath();
};

View2DTest.prototype.on_draw_preview = function(canvas, ctx) {
    ctx.fillStyle = "rgba(255,255,255,.4)";
    ctx.fillRect(-1000, -1000, 2000, 20000);

    ctx.lineWidth = .01;
    ctx.strokeTyle = "rgba(0,200,0,.4)";
    ctx.strokeRect(-1, -1, 2, 2);

    ctx.fillStyle = "rgba(200,0,0,.4)";
    ctx.fillRect(-.8, -.8, 1, 1);

    ctx.fillStyle = "rgba(0,0,200,.4)";
    ctx.beginPath();
    ctx.arc(0, 0, .5, 0, 2 * Math.PI, false);
    ctx.fill();
    ctx.closePath();
};

/* Graph2D_GraphInfo Class */

function Graph2D_GraphInfo() {
    this.xAxisH = 0;
    this.yAxisW = 0;
    this.ll = [0, 0];
    this.ur = [1, 1];
}

Graph2D_GraphInfo.prototype.toNDC = function(pt) {
    return [2 * (pt[0] - this.ll[0]) / (this.ur[0] - this.ll[0]) - 1,
            2 * (pt[1] - this.ll[1]) / (this.ur[1] - this.ll[1]) - 1];
};

Graph2D_GraphInfo.prototype.fromNDC = function(pt) {
    return [this.ll[0] + (this.ur[0] - this.ll[0]) * (pt[0] + 1) * .5,
            this.ll[1] + (this.ur[1] - this.ll[1]) * (pt[1] + 1) * .5];
};

/* Graph2D_PlotStyle Class */

function Graph2D_PlotStyle() {
}

Graph2D_PlotStyle.prototype.plot = function(graph, ctx, data) {};

/* Graph2D_LinePlotStyle Class */

function Graph2D_LinePlotStyle(width, color) {
    Graph2D_PlotStyle.call(this);

    if (!width)
        width = 1;
    if (!color)
        color = [0,0,0];

    this.width = width;
    this.color = color;
}
Graph2D_LinePlotStyle.prototype = new Graph2D_PlotStyle();
Graph2D_LinePlotStyle.prototype.constructor = Graph2D_LinePlotStyle;

Graph2D_LinePlotStyle.prototype.plot = function(graph, ctx, data) {
    if (data.length === 0)
        return;

    ctx.beginPath();
    var co = graph.graphInfo.toNDC(data[0]);
    ctx.moveTo(co[0], co[1]);
    for (var i = 1, e = data.length; i != e; ++i) {
        var co = graph.graphInfo.toNDC(data[i]);
        ctx.lineTo(co[0], co[1]);
    }
    ctx.lineWidth = this.width * (graph.getPixelSize()[0] + graph.getPixelSize()[1]) * .5;
    ctx.strokeStyle = col3_to_rgb(this.color);
    ctx.stroke();
};

/* Graph2D_PointPlotStyle Class */

function Graph2D_PointPlotStyle(width, color) {
    Graph2D_PlotStyle.call(this);

    if (!width)
        width = 1;
    if (!color)
        color = [0,0,0];

    this.width = width;
    this.color = color;
}
Graph2D_PointPlotStyle.prototype = new Graph2D_PlotStyle();
Graph2D_PointPlotStyle.prototype.constructor = Graph2D_PointPlotStyle;

Graph2D_PointPlotStyle.prototype.plot = function(graph, ctx, data) {
    if (data.length === 0)
        return;

    ctx.beginPath();
    var radius = this.width * (graph.getPixelSize()[0] + graph.getPixelSize()[1]) * .5;
    for (var i = 0, e = data.length; i != e; ++i) {
        var co = graph.graphInfo.toNDC(data[i]);
        ctx.moveTo(co[0], co[1]);
        ctx.arc(co[0], co[1], radius, 0, Math.PI * 2, /*anticlockwise=*/false);
    }
    ctx.fillStyle = col3_to_rgb(this.color);
    ctx.fill();
};

/* Graph2D_ErrorBarPlotStyle Class */

function Graph2D_ErrorBarPlotStyle(width, color) {
    Graph2D_PlotStyle.call(this);

    if (!width)
        width = 1;
    if (!color)
        color = [0,0,0];

    this.width = width;
    this.color = color;
}
Graph2D_ErrorBarPlotStyle.prototype = new Graph2D_PlotStyle();
Graph2D_ErrorBarPlotStyle.prototype.constructor = Graph2D_ErrorBarPlotStyle;

Graph2D_ErrorBarPlotStyle.prototype.plot = function(graph, ctx, data) {
    if (data.length === 0)
        return;

    ctx.beginPath();
    for (var i = 0, e = data.length; i != e; ++i) {
        var co_min = graph.graphInfo.toNDC([data[i][0], data[i][1]]);
        var co_max = graph.graphInfo.toNDC([data[i][0], data[i][2]]);
        ctx.moveTo(co_min[0], co_min[1]);
        ctx.lineTo(co_max[0], co_max[1]);
    }
    ctx.lineWidth = this.width * (graph.getPixelSize()[0] + graph.getPixelSize()[1]) * .5;
    ctx.strokeStyle = col3_to_rgb(this.color);
    ctx.stroke();
};

/* Graph2D_RangePlotStyle Class */

function Graph2D_RangePlotStyle(color) {
    Graph2D_PlotStyle.call(this);
    
    this.doNotUseForLayout = true;
    if (color === null)
        color = [0,1,0];
    
    this.fill_color = color;
    this.fill_color[this.fill_color.length] = 0.25;  
    this.initial_line_width = null;
}

Graph2D_RangePlotStyle.prototype = new Graph2D_PlotStyle();
Graph2D_RangePlotStyle.prototype.constructor = Graph2D_RangePlotStyle;

Graph2D_RangePlotStyle.prototype.plot = function(graph, ctx, data) {
    ctx.save();
    
    var gi = graph.graphInfo;
    
    var line_base = Math.max(graph.getPixelSize()[0], graph.getPixelSize()[1]);
    
    // We want our highlight to be darker when we are zoomed out further and lighter
    // when we are closer in. An exponential heuristic based off of line_base seems
    // to work nicely.
    if (this.initial_line_width === null)
        this.initial_line_width = line_base;
    
    var opacity = 1.0;
    if (this.initial_line_width > line_base) {
        var delta = (line_base - this.initial_line_width)/this.initial_line_width;
        delta = delta*delta;
        var expo = Math.exp(-8*delta);        
        opacity = Math.max(expo, 0.25);
    }
    
    var fill_color = this.fill_color;
    fill_color[3] = opacity;
    ctx.fillStyle = col4_to_rgba(fill_color);    
    
    var lower_rev = [data[0], gi.ll[1]];
    var upper_rev = [data[1], gi.ur[1]];
    
    var lower_graph = gi.toNDC(lower_rev);
    var upper_graph = gi.toNDC(upper_rev);
    
    var origin_x = lower_graph[0];
    var origin_y = lower_graph[1];
    var width = upper_graph[0] - lower_graph[0];
    var height = upper_graph[1] - lower_graph[1];
    
    ctx.fillRect(origin_x, origin_y, width, height);
    
    ctx.restore();
};

/* Graph2D_Axis Class */

function Graph2D_Axis(dir, format) {
    if (!format)
        format = this.formats.normal;

    this.dir = dir;
    this.format = format;
}

// Static Methods
Graph2D_Axis.prototype.formats = {
    normal: function(value, iDigits, fDigits) {
        // FIXME: iDigits?
        return value.toFixed(fDigits);
    },
    day: function(value, iDigits, fDigits) {
        var date = new Date(value * 1000.);
        var res = date.getUTCFullYear();
        res += "-" + (date.getUTCMonth() + 1);
        res += "-" + (date.getUTCDate() + 1);
        return res;
    }
};

Graph2D_Axis.prototype.draw = function(graph, ctx, ll, ur, mainUR) {
    var dir = this.dir, ndir = 1 - this.dir;
    var vMin = ll[dir];
    var vMax = ur[dir];
    var near = ll[ndir];
    var far = ur[ndir];
    var border = mainUR[ndir];

    var line_base = (graph.getPixelSize()[0] + graph.getPixelSize()[1]) * .5;
    ctx.lineWidth = 2 * line_base;
    ctx.strokeStyle = "rgb(0,0,0)";

    ctx.beginPath();
    var co = vec2_cswap([vMin, far], dir);
    co = graph.graphInfo.toNDC(co);
    ctx.moveTo(co[0], co[1]);
    var co = vec2_cswap([vMax, far], dir);
    co = graph.graphInfo.toNDC(co);
    ctx.lineTo(co[0], co[1]);
    ctx.stroke();

    var delta = vMax - vMin;
    var steps = Math.floor(Math.log(delta) / Math.log(10));
    if (delta / Math.pow(10, steps) >= 5.0) {
        var size = .5;
    } else if (delta / Math.pow(10, steps) >= 2.5) {
        var size = .25;
    } else {
        var size = .1;
    }
    size *= Math.pow(10, steps);

    if (steps <= 0) {
        var iDigits = 0, fDigits = 1 + Math.abs(steps);
    } else {
        var iDigits = steps, fDigits = 0;
    }

    var start = Math.ceil(vMin / size);
    var end = Math.ceil(vMax / size);

    // FIXME: Draw in window coordinates to make crisper.

    // FIXME: Draw grid in layers to avoid ugly overlaps.

    for (var i = start; i != end; ++i) {
        if (i == 0) {
            ctx.lineWidth = 3 * line_base;
            var p = .5;
        } else if (!(i & 1)) {
            ctx.lineWidth = 2 * line_base;
            var p = .5;
        } else {
            ctx.lineWidth = 1 * line_base;
            var p = .75;
        }

        ctx.beginPath();
        var co = vec2_cswap([i * size, lerp(near, far, p)], dir);
        co = graph.graphInfo.toNDC(co);
        ctx.moveTo(co[0], co[1]);
        var co = vec2_cswap([i * size, far], dir);
        co = graph.graphInfo.toNDC(co);
        ctx.lineTo(co[0], co[1]);
        ctx.stroke();
    }

    for (var alt = 0; alt < 2; ++alt) {
        if (alt)
            ctx.strokeStyle = "rgba(190,190,190,.5)";
        else
            ctx.strokeStyle = "rgba(128,128,128,.5)";
        ctx.lineWidth = 1 * line_base;
        ctx.beginPath();
        for (var i = start; i != end; ++i) {
            if (i == 0)
                continue;
            if ((i & 1) == alt) {
                var co = vec2_cswap([i * size, far], dir);
                co = graph.graphInfo.toNDC(co);
                ctx.moveTo(co[0], co[1]);
                var co = vec2_cswap([i * size, border], dir);
                co = graph.graphInfo.toNDC(co);
                ctx.lineTo(co[0], co[1]);
            }
        }
        ctx.stroke();

        if (start <= 0 && 0 < end) {
            ctx.beginPath();
            var co = vec2_cswap([0, far], dir);
            co = graph.graphInfo.toNDC(co);
            ctx.moveTo(co[0], co[1]);
            var co = vec2_cswap([0, border], dir);
            co = graph.graphInfo.toNDC(co);
            ctx.lineTo(co[0], co[1]);
            ctx.strokeStyle = "rgba(64,64,64,.5)";
            ctx.lineWidth = 3 * line_base;
            ctx.stroke();
        }
    }

    // FIXME: Draw this in screen coordinates, and stop being stupid. Also,
    // figure out font height?
    if (this.dir == 1) {
        var offset = [-.5, -.25];
    } else {
        var offset = [-.5, 1.1];
    }
    ctx.fillStyle = "rgb(0,0,0)";
    var pxl = graph.getPixelSize();
    for (var i = start; i != end; ++i) {
        if ((i & 1) == 0) {
            var label = this.format(i * size, iDigits, fDigits);
            ctx.save();
            var co = vec2_cswap([i*size, lerp(near, far, .5)], dir);
            co = graph.graphInfo.toNDC(co);
            ctx.translate(co[0], co[1]);
            ctx.scale(pxl[0], -pxl[1]);
            // FIXME: Abstract.
            var bb_w = label.length * 5;
            if (ctx.measureText != null)
                bb_w = ctx.measureText(label).width;
            var bb_h = 12;
            // FIXME: Abstract? Or ignore.
            if (ctx.fillText != null) {
                ctx.fillText(label, bb_w*offset[0], bb_h*offset[1]);
            } else if (ctx.mozDrawText != null) {
                ctx.translate(bb_w*offset[0], bb_h*offset[1]);
                ctx.mozDrawText(label);
            }
            ctx.restore();
        }
    }
};


/* Graph2D Class */

function Graph2D(canvasname) {
    View2D.call(this, canvasname);

    this.useWidgets = false;
    this.plots = [];
    this.graphInfo = null;
    this.xAxis = new Graph2D_Axis(0);
    this.yAxis = new Graph2D_Axis(1);
    this.debugText = null;

    this.clearColor = [.8, .8, .8];
}
Graph2D.prototype = new View2D();
Graph2D.prototype.constructor = Graph2D;

//

Graph2D.prototype.graphChanged = function() {
    this.graphInfo = null;
    // FIXME: Need event loop.
    this.refresh();
};

Graph2D.prototype.layoutGraph = function() {
    var gi = new Graph2D_GraphInfo();

    gi.xAxisH = 40;
    gi.yAxisW = 60;

    var min = null, max = null;
    for (var i = 0, e = this.plots.length; i != e; ++i) {
        var data = this.plots[i][0];
        var style = this.plots[i][1];
        
        // Some styles (i.e. Graph2D_RangePlotStyle) do not want to be considered
        // for layout purposes, so we ignore them.
        if (style.doNotUseForLayout === true)
            continue;
        
        for (var i2 = 0, e2 = data.length; i2 != e2; ++i2) {
            if (min == null)
                min = data[i2];
            else
                min = vec2_min(min, data[i2]);

            if (max == null)
                max = data[i2];
            else
                max = vec2_max(max, data[i2]);
        }
    }

    if (min === null)
        min = [0, 0];
    if (max === null)
        max = [0, 0];
    if (Math.abs(max[0] - min[0]) < .001)
        max[0] += 1;
    if (Math.abs(max[1] - min[1]) < .001)
        max[1] += 1;

    // Set graph transform to the [min,max] rect to the content area with
    // some padding.
    //
    // FIXME: Add real mat3 and implement this properly.
    var pad = 5;
    var vd = new ViewData();
    var ll_target = this.convertClientToWorld([gi.yAxisW + pad, gi.xAxisH + pad], vd);
    var ur_target = this.convertClientToWorld(vec2_subN(this.size, pad), vd);
    var target_size = vec2_sub(ur_target, ll_target);
    var target_center = vec2_add(ll_target, vec2_mulN(target_size, .5));

    var center = vec2_mulN(vec2_add(min, max), .5);
    var size = vec2_sub(max, min);

    var scale = vec2_mulN(target_size, .5);
    size = vec2_div(size, scale);
    center = vec2_sub(center, vec2_mulN(vec2_mul(target_center, size), .5));

    gi.ll = vec2_sub(center, vec2_mulN(size, .5));
    gi.ur = vec2_add(center, vec2_mulN(size, .5));

    return gi;
};

//

Graph2D.prototype.convertClientToGraph = function(pt) {
    return this.graphInfo.fromNDC(this.convertClientToWorld(pt));
};

//

Graph2D.prototype.on_size_change = function() {
    this.graphInfo = null;
};

Graph2D.prototype.on_draw_start = function() {
    if (!this.graphInfo)
        this.graphInfo = this.layoutGraph();
};

Graph2D.prototype.on_draw = function(canvas, ctx) {
    var gi = this.graphInfo;
    var w = this.size[0], h = this.size[1];

    this.xAxis.draw(this, ctx,
                    this.convertClientToGraph([gi.yAxisW, 0]),
                    this.convertClientToGraph([w, gi.xAxisH]),
                    this.convertClientToGraph([w, h]));
    this.yAxis.draw(this, ctx,
                    this.convertClientToGraph([0, gi.xAxisH]),
                    this.convertClientToGraph([gi.yAxisW, h]),
                    this.convertClientToGraph([w, h]));

    if (this.debugText != null) {
        ctx.save();
        ctx.setTransform(1, 0, 0, 1, 0, 0);
        ctx.fillText(this.debugText, this.size[0]/2 + 10, this.size[1]/2 + 10);
        ctx.restore();
    }

    // Draw the contents.
    ctx.save();
    ctx.beginPath();
    var content_ll = this.convertClientToWorld([gi.yAxisW, gi.xAxisH]);
    var content_ur = this.convertClientToWorld(this.size);
    ctx.rect(content_ll[0], content_ll[1],
             content_ur[0]-content_ll[0], content_ur[1]-content_ll[1]);
    ctx.clip();

    for (var i = 0, e = this.plots.length; i != e; ++i) {
        var data = this.plots[i][0];
        var style = this.plots[i][1];
        style.plot(this, ctx, data);
    }
    ctx.restore();
};

// Client API.

Graph2D.prototype.clearPlots = function() {
    this.plots = [];
    this.graphChanged();
};

Graph2D.prototype.addPlot = function(data, style) {
    if (!style)
        style = new Graph2D_LinePlotStyle(1);
    this.plots.push( [data, style] );
    this.graphChanged();
};

