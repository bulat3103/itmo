select person.id, person.age,
       case when result.effect = 95 then action.id else result.effect end
from person
         join person_profession on person.id = person_profession.person_id
         join opinion on person.id = opinion.person_id
         join science on science.id = opinion.science_id
         join result on science.id = result.science_id
         join action on result.action_id = action.id
where person.gender = 'FEMALE' and result.effect > 91
group by person.id, person.age, science.start_time, result.effect, action.id
having count(*) < 5
order by person.age, science.start_time, result.effect limit 1