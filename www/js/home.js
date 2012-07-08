
$.extend(widgets, {
  home : ({
    draw : function() {
      include('/js/navMenu.js');
      widgets.navMenu.draw();
    }
  })
});
