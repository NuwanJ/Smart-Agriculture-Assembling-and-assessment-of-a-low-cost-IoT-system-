module.exports = {
   config:{
      baseURL: 'http://' + process.env.HOST+ ':' + process.env.PORT,
      timeout: 1000,
      headers: {'X-Custom-Header': ''}
   }
}
