'use strict';

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _express = require('express');

var _express2 = _interopRequireDefault(_express);

var _path = require('path');

var _path2 = _interopRequireDefault(_path);

var _morgan = require('morgan');

var _morgan2 = _interopRequireDefault(_morgan);

var _http = require('http');

var _http2 = _interopRequireDefault(_http);

var _osc = require('osc');

var _osc2 = _interopRequireDefault(_osc);

var _milkcocoa = require('milkcocoa');

var _milkcocoa2 = _interopRequireDefault(_milkcocoa);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var SERVER_PORT = '8080';
var UDP_PORT = '7777';
var P5_PORT = '12345';

var App = function () {
    function App() {
        var _this = this;

        _classCallCheck(this, App);

        this.exp = (0, _express2.default)();
        this.exp.use((0, _morgan2.default)('dev'));

        var port = parseInt(SERVER_PORT, 10);
        this.exp.set('port', port);

        this.server = _http2.default.createServer(this.exp);
        this.server.listen(port);
        this.server.on('error', this.onError.bind(this));
        this.server.on('listening', this.onListening.bind(this));

        this.udpPort = new _osc2.default.UDPPort({
            localAddress: '0.0.0.0',
            localPort: UDP_PORT,
            metadata: true
        });

        this.udpPort.open();

        this.exp.get('/light', function (req, res) {

            if (req.query.p) {
                res.send('success');

                var param = req.query.p;

                _this.udpPort.send({
                    address: '/',
                    args: [{ type: 'i', value: param - 0 }]
                }, '0.0.0.0', P5_PORT);

                console.log('++send++');
                console.log('query: ' + param);
                console.log('++ - - ++');
            } else {
                res.send('fail');
            }
        });

        this.milkcocoa = _milkcocoa2.default.connectWithApiKey('bluejcw1ch34.mlkcca.com', 'HJKKNPPHCNNJDKIL', 'hAYYdlfJaUJUCSKIegQEQaaWUTHfDjTQMgODXkhf');
        this.dataStore = this.milkcocoa.dataStore('light');
        this.dataStore.on('send', function (e) {
            console.log(e);

            if (e.path === 'light') {
                _this.udpPort.send({
                    address: '/',
                    args: [{ type: 'i', value: e.value }]
                }, '0.0.0.0', P5_PORT);
            }
        });
    }

    _createClass(App, [{
        key: 'onError',
        value: function onError(error) {
            if (error.syscall !== 'listen') {
                throw error;
            }

            var bind = typeof port === 'string' ? 'Pipe ' + port : 'Port ' + port;

            switch (error.code) {
                case 'EACCESS':
                    console.error(bind + ' requires elevated priviledges');
                    process.exit(1);
                    break;
                case 'EADDRINUSE':
                    console.error(bind + ' is already in use');
                    process.exit(1);
                    break;
                default:
                    throw error;
            }
        }
    }, {
        key: 'onListening',
        value: function onListening() {
            var addr = this.server.address();
            var bind = typeof addr === 'string' ? 'Pipe ' + addr : 'Port ' + addr.port;

            console.log('Listening on ' + bind);
        }
    }]);

    return App;
}();

var app = new App();
//# sourceMappingURL=app.js.map
