function split( val) {
  //return val.split( /,\s*/ );
  return val.split(/,\s*/);
}

function extractLast( term) {
    return split( term).pop();
}

var os = 0;
var oe = 0;

$.extend(widgets, {
  search : ({
    table : ({
      drawSpinner : function() {
        if($('div#_searchContainer').length > 0)
        {
          //console.log("div#_searchContainer exists, destroying");
          $('div#_searchContainer').fadeOut(1000);
          $('div#_searchContainer').empty().remove();

        }
        $('body').append(
          $('<div></div>').attr({
            id : '_searchContainer',
            name : '_searchContainer',
            class : '_searchContainer'
          }).append(
            $('<img></img>').attr({
              src : '/images/small-spinner.gif'
            })
          )
        )
      },
      draw : function(search_results) {
        if($('div#_searchContainer').length > 0)
        {
          //console.log("div#_searchContainer exists, destroying");
          $('div#_searchContainer').fadeOut(1000);
          $('div#_searchContainer').empty().remove();
          
        }
        $('body').append(
          $('<div></div>').attr({
            id : '_searchContainer',
            name : '_searchContainer',
            class : '_searchContainer'
          }).append(
            $('<table></table>').attr({
              id : '_searchResults',
              name : '_searchResults',
              class : '_searchResults'
            })
          )
        );
        //<tr class="SR" BGCOLOR="#eeeeee"><th  class="SRD">date</th><th class="SRD">host</th><th class="SRD">inputFile</th><th  class="SRD" >content</th></tr>
        $('table#_searchResults').append(
          $('<tr></tr>').attr({
            class: "SR"
          }).append(
            $('<th></th>').attr({
              class : 'SRD'
            }).text('date'),
            $('<th></th>').attr({
              class : 'SRD'
            }).text('host'),
            $('<th></th>').attr({
              class : 'SRD'
            }).text('input'),
            $('<th></th>').attr({
              class : 'SRD'
            }).text('content')
          )
        );
        for(i in search_results)
        {
          $('table#_searchResults').append(
            $('<tr></tr>').append(
              $('<td></td>').attr({
                class : "sortable"
              }).text(search_results[i]['date']),
              $('<td></td>').attr({
                class : "sortable"
              }).text(search_results[i]['host']),
              $('<td></td>').attr({
                class : "sortable"
              }).text(search_results[i]['input']),
              $('<td></td>').attr({
                class : "sortable"
              }).text($.base64.decode(search_results[i]['content']))
            )
          );
          //console.log("search_results: ");
          //console.log(search_results[i]['date']); 
        }
        $('div#_searchContainer').fadeIn(2000);
        
      }
    }),
    lastCommand : "",
    searchCommands : [
      {
        label : 'dateFrom',
        value : 'dateFrom:'
      },
      {
        label : 'dateTo',
        value : 'dateTo:'
      },
      {
        label : 'hosts',
        value : 'hosts:'
      },
      {
        label : 'inputs',
        value : 'inputs:'
      },
      {
        label : 'query',
        value : 'query:'
      },
      {
        label : 'sortBy',
        value : 'sortBy:'
      }
    ],
    searchables : {
      "hosts" : [
        //{
        //  label : 'myvpv01.corp.verifi.com',
        //  value : 'myvpv01.corp.verifi.com'
        //},
        //{
        //  label : 'cdrn3dbsv01.corp.verifi.com',
        //  value : 'cdrn3dbsv01.corp.verifi.com'
        //}
      ],
      "inputs" : []
    },
    parseQueryAndSubmit : function() {

      widgets.search.table.drawSpinner();

      var jquery_data = "";;
      var split_queryInput = $("input#_queryInput")[0].value.split(/", /);
      var i = 0;
      for (i=0;i<split_queryInput.length-1;i++)
      {
        
        console.log("jquery_data: " + jquery_data);
        jquery_data += split_queryInput[i].split(/:/)[0];
        jquery_data += '=';
        if(split_queryInput[i].split(/:/)[0] == "dateFrom" || split_queryInput[i].split(/:/)[0] == "dateTo")
        {
          var dateData = '';
          try
          {
            jquery_data += new String(Date.parse(split_queryInput[i].split(/:/)[1].substring(1, split_queryInput[i].split(/:/)[1].length)).valueOf()).substring(0,10);
          } catch(e) {
            alert("Error: could not parse " + split_queryInput[i].split(/:/)[0] + "\nbad formatting: " + e + "\n" + split_queryInput[i].split(/:/)[1].substring(1, split_queryInput[i].split(/:/)[1].length));
            return 1;
          }
        } else {
          console.log("jquery_data: " + jquery_data);
          jquery_data += split_queryInput[i].split(/:/)[1].substring(1, split_queryInput[i].split(/:/)[1].length);
          console.log("jquery_data: " + jquery_data + "\n\n");
        }
        jquery_data += '&';  
      }
      jquery_data = jquery_data.substring(0, jquery_data.length - 1);
      $.ajax({
        url : "/api",
        type : "GET",
        async : true,
        headers : {
          'x-stump-action' : 'search'
        },
        data : jquery_data,
        success : function(data, textStatus, jqXHR) {
          var json_data = eval(data);
          widgets.search.table.draw(json_data);
          delete json_data;
        }
      });
    },
    menu : ({
      sources : [{}],
      getInputs : function() {
        $.ajax({
          url : "/api",
          type : "GET",
          async : true,
          headers : {
          'x-stump-action' : 'getInputs'
          },
          success : function(data, textStatus, jqXHR) {
            var json_data = eval(data);
            for(i in json_data.inputs)
            {
              widgets.search.searchables.inputs.push({label : json_data.inputs[i], value : json_data.inputs[i]});
            }
            delete json_data;
          }
        });
      },
      getHosts : function() {
        $.ajax({
          url : "/api",
          type : "GET",
          async : true,
          headers : {
            'x-stump-action' : "getHosts"
          },
          success : function(data, textStatus, jqXHR) {
            var json_data = eval(data);
            alert(JSON.stringify(json_data));
            for(i in json_data.hosts)
            {
              widgets.search.searchables.hosts.push({label : json_data.hosts[i], value : json_data.hosts[i]});
            }
            delete json_data;
          }
        });
      },
      draw : function() {
        widgets.search.menu.getInputs();
        widgets.search.menu.getHosts();
        $('body').append(
          $('<br />'),
          $('<input></input>').attr({
            id : '_queryInput',
            name : '_queryInput',
            class : '_queryInput'
          }),
          $('<br />'),
          $('<br />'),
          $('<a></a>').attr({
            id : '_queryInput_submit',
            name : '_queryInput_submit',
            class : '_queryInput_submit',
            href : 'Javascript: widgets.search.parseQueryAndSubmit();'
          }).text("Submit")
        );
      },
      getAutoComplete : function(obj, str)
      {
        $.grep(widgets.search.searchCommands, function(item){
          if (item.label == str)
          {
            alert(item.data);
          }
        });
      }
    }),
    draw : function() {
      widgets.navMenu.draw();
      widgets.search.menu.draw();
      $(document).ready(function() {
        $('input#_queryInput').autocomplete({
          delay: 50,
          source: function( request, response ) {
            // determine if cursor is between two quotes
            if(request.term.substring(request.term.length - 3,request.term.length) == '", ')
            {
              var delim;

              var startPos,endPos;

              var position = $('input#_queryInput')[0].selectionStart;
              while(delim != ':' && position > 0)
              {
                delim = $('input#_queryInput')[0].value.substring(--position, position+1) ;
              }
              //alert("Found delimiter " + delim + " at position: " + position + " and search term is " + ui.item.value);
              endPos = position;

              while(delim != ' ' && position > 0)
              {
                delim = $('input#_queryInput')[0].value.substring(--position, position+1) ;
              }
              startPos = position;
              var currentCommand = $('input#_queryInput')[0].value.substring(startPos, endPos).trim();

              var terms = request.term.split(/"/);
              function term_position(term_buf) {
                var total_size = 0;
                var i;
                for(i=0;i<term_buf.length;i++)
                {
                  total_size += term_buf[i].length;
                  if($('input#_queryInput')[0].selectionStart <= total_size)
                  {
                    return --i;
                  } 
                }
                return i-2;
              }
              if(widgets.search.searchables[currentCommand])
              {
                if(terms[term_position(terms)].match(/,/) != null)
                {
                  var sub_terms = terms[term_position(terms)].split(/,/);
                  response( $.ui.autocomplete.filter(
                    widgets.search.searchables[currentCommand], sub_terms.pop() ) );
                } else {
                  response( $.ui.autocomplete.filter(
                    widgets.search.searchables[currentCommand], terms[term_position(terms)] ) );
                }
              }
            } else {
            response( $.ui.autocomplete.filter(
	      widgets.search.searchCommands, extractLast( request.term ) ) );
            }
          },
          focus: function() {
            // prevent value inserted on focus
            return false;
          },
          select: function( event, ui ) {
            
            if($('input#_queryInput')[0].value.substring($('input#_queryInput')[0].selectionStart, $('input#_queryInput')[0].selectionStart + 1) == '"')
            {
              //find previous comma, or quotation mark
              var delim;
              var position = $('input#_queryInput')[0].selectionStart;
              while(delim != ',' && delim != '"' && position > 0)
              {
                delim = $('input#_queryInput')[0].value.substring(--position, position+1) ;
              }
              //alert("Found delimiter " + delim + " at position: " + position + " and search term is " + ui.item.value);

              $('input#_queryInput')[0].value = $('input#_queryInput')[0].value.substring(0, position+1) + ui.item.value + $('input#_queryInput')[0].value.substring($('input#_queryInput')[0].selectionStart, $('input#_queryInput')[0].value.length);

              //var terms = split( this.value );
              //terms.pop();
              //terms.push( ui.item.value );
              //terms.push( '' );
              //this.value = terms.join( ',' );

            } else {
              var terms = split( this.value );
              terms.pop();
              terms.push( ui.item.value + '""' );
              terms.push( '' );
              this.value = terms.join( ', ' );
              $('input#_queryInput')[0].setSelectionRange(
                 this.value.length - 3,
                 this.value.length - 3
               );
             }
            //widgets.search.menu.getAutoComplete($('input#_queryInput')[0],ui.item.label);
            //alert(ui.item.data);
            //$('input#_queryInput').autocomplete( "option", "source", function(request, response) {
            //     console.log($.ui.autocomplete.filter(
            //      widgets.search.searchCommands, extractLast( request.term, /"*",/ ) ));
            //    response( $.ui.autocomplete.filter(
            //      widgets.search.searchHosts, extractLast( request.term, /"*",/ ) ) );
            //  }
            //);
            /*
            $('input#_queryInput').autocomplete( "option", "select", function(event, ui) {
               var terms = split( this.value );
               terms.pop();
               terms.push( ui.item.value);
               terms.push( '' );
               this.value = terms.join( ", " );
              }
            );
            */
            return false;
          }
        });              
      });
    }
  })
});
