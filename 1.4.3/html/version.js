document.addEventListener("DOMContentLoaded", function() {
  var versions = [ //ATTN:  version, path. First one is the default. add when new version is released.
    ['latest-stable', '/latest-stable'],
    ['1.3.0', '/1.3.0'],
    ['1.4.1', '/1.4.1'],
    ['1.4.2', '/1.4.2'],
    ['1.4.3', '/1.4.3'],
  ];
  var h = '<select>';
  var current_ver = $("#projectnumber")[0].innerText || versions[0][0];
  for (i = 0; i < versions.length; i++) {
      selected = ''
      if (current_ver === versions[i][0])
          selected = ' selected="selected"';
      h += '<option value="' + versions[i][0] + '"' + selected + '>' + versions[i][0] + '</option>';
  }
  h += '</select>';
  $("#projectnumber")[0].innerHTML = h;
  $("#projectnumber select")[0].addEventListener('change', function() {
      var v = $(this).children('option:selected').attr('value');
      var path = undefined;
      for (i = 0; i < versions.length; i++) {
          if (v === versions[i][0]) {
              path = versions[i][1];
              break;
          }
      }
      if (path) {
          var location = window.location;
          var url = location.href;
          var repo_name = /\/[^\/]+/.exec(location.pathname)
          var repo_path_url = location.pathname.replace(repo_name, '');
          console.log(url);
          var new_url = url.replace(window.location.hostname + repo_name + '/' + current_ver, window.location.hostname + repo_name + path);
          if (url == new_url) {
              var current_ver = /\/[^\/]+/.exec(repo_path_url)
              new_url = url.replace(window.location.hostname + repo_name + current_ver, window.location.hostname + repo_name + path);
          }
          console.log(new_url);
          if (url != new_url)
              window.location.href = new_url;
      }
  });
  return current_ver;
});