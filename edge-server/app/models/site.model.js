
module.exports = (sequelize, Sequelize) => {
   const Site = sequelize.define("site", {
      id: {
         type: Sequelize.INTEGER(4).UNSIGNED,
         primaryKey: true,
      },
      title:{
         type: Sequelize.TEXT
      },
      controllerId:{
         type: Sequelize.INTEGER(4).UNSIGNED
      },
      status:{
         type: Sequelize.ENUM('ACTIVE','DEACTIVE','TEST')
      },
      width:{
         type: Sequelize.INTEGER(4).UNSIGNED
      },
      length:{
         type: Sequelize.INTEGER(4).UNSIGNED
      },
      notes:{
         type: Sequelize.TEXT
      }
   },{
      timestamps: true,
      updatedAt: "lastUpdate",
      tableName: "sites"
   });

   return Site;
};
