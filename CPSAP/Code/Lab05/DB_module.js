var util = require('util');
var ee = require('events');


var db_data = [
                {id:1, name:'Иванов и.и.', bday: '2001-01-01'},
                {id:2, name:'Петров п.п.', bday: '2001-01-02'},
                {id:3, name:'Сидоров с.с.', bday: '2001-01-03'},
]


var commit_count = 0;


function DB(){

    this.select = ()=>{
        return db_data;
    }

    this.insert = (data)=>{
        let found_id;

        if(data.id == null)
            found_id=1;
        else 
            found_id = parseInt(data.id);


        while(true){
            if(db_data.findIndex(item => item.id == found_id) != -1)
                found_id = found_id + 1;
            else
                break;
        }


        let checked_data = {id: found_id, name:data.name, bday:data.bday};
        db_data.push(checked_data)

    }


    this.update = (updated_data) => {
        const index = db_data.findIndex(item => item.id == updated_data.id);

        if(index == -1)
                return false;

        db_data[index] = updated_data;
        return true;

    }


    this.delete = (id) => {
        const index = db_data.findIndex(item => item.id == id)
        if(index == -1)
            return false;

        const deletedRow = db_data.splice(index, 1)[0];
        return deletedRow;
    }


    this.commit = () =>{
        console.log("Commite successful");
        return ++commit_count;
    }


}





util.inherits(DB, ee.EventEmitter);
exports.DB = DB;


