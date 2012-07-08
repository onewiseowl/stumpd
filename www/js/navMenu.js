$.extend(widgets, {
  navMenu : ({
    draw : function() {
      $('body').append(
        $('<div></div>').attr({
          id : '_navMenu',
          name : '_navMenu',
          class : '_navMenu'
        }).append(
          $('<a></a>').attr({
            href : '/home'
          }).html('home')
        )
      )
    }
  })
});
