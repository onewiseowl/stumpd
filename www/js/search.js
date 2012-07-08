
$.extend(widgets, {
  search : ({
    menu : ({
      sources : [{}],
      getSources : function() {
        $.ajax({
          url : "/api",
          type : "GET",
          data : {
            action : "getSources"
          },
          success : function(data, textStatus, jqXHR) {
            this.sources = (data);
            alert(data);
          }
        });
      },
      draw : function() {
        widgets.search.menu.getSources();
      }
    }),
    draw : function() {
      include('/js/navMenu.js');
      widgets.navMenu.draw();
      widgets.search.menu.draw();
    }
  })
});
