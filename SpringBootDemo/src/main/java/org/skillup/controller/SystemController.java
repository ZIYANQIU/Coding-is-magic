package org.skillup.controller;

import org.springframework.web.bind.annotation.*;

@RestController
public class SystemController {
    @GetMapping("/name/id/{id}")
    public String getName(@PathVariable("id") String userId) {
        if (userId.equals("1")) {
            return "Welcome to SkillUp!";
        } else {
            return "Hello User!";
        }

    }

    @PostMapping("/user")
    public Person createUser(@RequestBody Person person) {
        person.age = person.getAge()+1;
        return person;
    }
}
