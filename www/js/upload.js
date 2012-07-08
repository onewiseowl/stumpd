$.extend(widgets, {
  upload : ({
    uploadBox : ({
      submit : function() {
        $('#_uploadBox_form').submit();
      },
      draw : function() {
        $('body').append(
          $('<div></div>').attr({
            id : '_uploadBox',
            name : '_uploadBox',
            class : '_uploadBox'
          }).append(
            $('<form></form>').attr({
              enctype : 'multipart/form-data',
              method : 'POST',
              action : '/api',
              id : '_uploadBox_form',
              name : '_uploadBox_form'
            }).append(
              $('<input></input>').attr({
                type : 'file',
                id : '_uploadBox_form_file_input',
                name : '_uploadBox_form_file_input'
              }),
              $('<input></input>').attr({
                type : 'hidden',
                id : '_uploadBox_form_action',
                name : 'action',
                value : 'upload',
              }),
              $('<a></a>').attr({
                href : 'Javascript: widgets.upload.uploadBox.submit()',
              }).html('Submit...')
            )
          )
        )
      }
    })
  })
});
