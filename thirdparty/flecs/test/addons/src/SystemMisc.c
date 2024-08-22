#include <addons.h>

static
int32_t dummy_invoked = false;

static
void Dummy(ecs_iter_t *it) {
    dummy_invoked = true;
    probe_iter(it);
}

void SystemMisc_invalid_not_without_id(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, !);

    ecs_fini(world);
}

void SystemMisc_invalid_optional_without_id(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, ?);

    ecs_fini(world);
}

void SystemMisc_invalid_entity_without_id(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_ENTITY(world, Foo, 0);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, FOO.);

    ecs_fini(world);
}

void SystemMisc_invalid_empty_element(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate,, Position);

    ecs_fini(world);
}

void SystemMisc_invalid_empty_element_w_space(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, , Position);

    ecs_fini(world);
}

void SystemMisc_invalid_empty_or(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, || Position);

    ecs_fini(world);
}

void SystemMisc_invalid_empty_or_w_space(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate,|| Position);

    ecs_fini(world);
}

void SystemMisc_invalid_or_w_not(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position || !Velocity);

    ecs_fini(world);
}

void SystemMisc_invalid_not_w_or(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, !Position || Velocity);

    ecs_fini(world);
}

void SystemMisc_invalid_0_w_and(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, 0, Position);

    ecs_fini(world);
}

void SystemMisc_invalid_0_w_from_entity(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();
    
    ECS_ENTITY(world, Foo, 0);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Foo.0);

    ecs_fini(world);
}

void SystemMisc_invalid_component_id(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position);

    ecs_fini(world);
}

void SystemMisc_invalid_entity_id(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    test_expect_abort();

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position(NotValid));

    ecs_fini(world);
}

void SystemMisc_invalid_null_string(void) {
    ecs_world_t *world = ecs_init();

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "Dummy", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .callback = Dummy
    });

    ecs_progress(world, 0);

    test_assert(dummy_invoked == true);

    ecs_fini(world);
}

void SystemMisc_invalid_empty_string(void) {
    ecs_world_t *world = ecs_init();

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "Dummy", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "",
        .callback = Dummy
    });

    ecs_progress(world, 0);

    test_assert(dummy_invoked == true);    

    ecs_fini(world);
}

void SystemMisc_invalid_empty_string_w_space(void) {
    ecs_world_t *world = ecs_init();

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "Dummy", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "  ",
        .callback = Dummy
    });

    ecs_progress(world, 0);

    test_assert(dummy_invoked == true);    

    ecs_fini(world);
}

void SystemMisc_redefine_row_system(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t s;
    {
        ECS_OBSERVER(world, Dummy, EcsOnAdd, Position);
        s = Dummy;
    }

    ECS_OBSERVER(world, Dummy, EcsOnAdd, Position);

    test_assert(s == Dummy);

    ecs_fini(world);
}

static int is_invoked;

static
void IsInvoked(ecs_iter_t *it) {
    is_invoked ++;
}

void SystemMisc_system_w_or_prefab(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);

    ECS_SYSTEM(world, IsInvoked, EcsOnUpdate, Position, flecs.core.Prefab || Disabled);

    test_int(is_invoked, 0);

    ecs_progress(world, 1);

    test_int(is_invoked, 1);

    ecs_fini(world);
}

void SystemMisc_system_w_or_disabled(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_ENTITY(world, Entity, Position, Disabled);

    ECS_SYSTEM(world, IsInvoked, EcsOnUpdate, Position, Prefab || Disabled);

    test_int(is_invoked, 0);

    ecs_progress(world, 1);

    test_int(is_invoked, 1);

    ecs_fini(world);
}

void SystemMisc_system_w_or_disabled_and_prefab(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_PREFAB(world, Prefab, Position);
    ECS_ENTITY(world, Entity, Position, Disabled);

    ECS_SYSTEM(world, IsInvoked, EcsOnUpdate, Position, flecs.core.Prefab || Disabled);

    test_int(is_invoked, 0);

    ecs_progress(world, 1);

    test_int(is_invoked, 2);
    is_invoked = false;

    ecs_fini(world);
}

static
void TableColumns(ecs_iter_t *it) {
    Position *p = ecs_field(it, Position, 0);
    Velocity *v = ecs_field(it, Velocity, 1);

    ecs_id_t ecs_id(Position) = ecs_field_id(it, 0);
    ecs_id_t ecs_id(Velocity) = ecs_field_id(it, 1);

    const ecs_type_t *type = ecs_table_get_type(it->table);
    test_int(2, type->count);

    ecs_entity_t *components = type->array;
    test_int(components[0], ecs_id(Position));
    test_int(components[1], ecs_id(Velocity));

    void *column_0 = ecs_table_get(it->real_world, it->table, Position, 0);
    test_assert(column_0 == p);

    void *column_1 = ecs_table_get(it->real_world, it->table, Velocity, 0);
    test_assert(column_1 == v);

    is_invoked ++;
}

void SystemMisc_table_columns_access(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world);
    ecs_add(world, e, Position);
    ecs_add(world, e, Velocity);

    ECS_SYSTEM(world, TableColumns, EcsOnUpdate, Position, Velocity);

    test_int(is_invoked, 0);

    ecs_progress(world, 1);

    test_int(is_invoked, 1);
    is_invoked = false;

    ecs_fini(world);
}

void SystemMisc_dont_enable_after_rematch(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_pair(world, ecs_id(Position), EcsOnInstantiate, EcsInherit);
    ecs_add_pair(world, ecs_id(Velocity), EcsOnInstantiate, EcsInherit);

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position(self|up IsA), Velocity(self|up IsA));

    /* Create an entity that is watched. Whenever components are added/removed
     * to and/or from watched entities, a rematch is triggered. */
    ECS_PREFAB(world, Prefab, Position);

    ECS_ENTITY(world, Entity, (IsA, Prefab));

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx, NULL);

    /* System is enabled but doesn't match with any entities */
    
    test_bool(ecs_has_id(world, Dummy, EcsDisabled), false);
    ecs_progress(world, 1);
    test_int(ctx.count, 0);

    /* Explicitly disable system before triggering a rematch */
    ecs_enable(world, Dummy, false);
    test_bool(ecs_has_id(world, Dummy, EcsDisabled), true);

    /* Trigger a rematch. System should still be disabled after this */
    ecs_add(world, Prefab, Velocity);
    test_bool(ecs_has_id(world, Dummy, EcsDisabled), true);

    ecs_progress(world, 1);
    test_int(ctx.count, 0);

    /* Enable system. It is matched, so should now be invoked */
    ecs_enable(world, Dummy, true);
    test_bool(ecs_has_id(world, Dummy, EcsDisabled), false);

    ecs_progress(world, 1);
    test_int(ctx.count, 1);

    ecs_fini(world);
}

static void SysA(ecs_iter_t *it)
{
    ecs_id_t ecs_id(Velocity) = ecs_field_id(it, 1);
    ecs_add(it->world, it->entities[0], Velocity);
}

static int b_invoked;
static ecs_entity_t b_entity;

static void SysB(ecs_iter_t *it)
{
    b_invoked ++;
    b_entity = it->entities[0];
}

void SystemMisc_ensure_single_merge(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_SYSTEM(world, SysA, EcsOnLoad, Position, [out] !Velocity);
    ECS_SYSTEM(world, SysB, EcsPostLoad, Velocity);

    ECS_ENTITY(world, MyEntity, Position);

    ecs_progress(world, 0);

    test_assert(b_invoked == 1);

    ecs_fini(world);
}

void SystemMisc_match_system(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_SYSTEM(world, SysA, 0, Position(SysA));
    ECS_SYSTEM(world, SysB, 0, Position);

    ecs_run(world, SysB, 0, NULL);

    test_assert(b_invoked != 0);
    test_assert(b_entity == SysA);
    
    ecs_fini(world);
}

void SystemMisc_system_initial_state(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, SysA, 0, Position);

    test_assert( ecs_has_id(world, SysA, EcsEmpty));
    test_assert( !ecs_has_id(world, SysA, EcsDisabled));

    ecs_fini(world);
}

static
void FooSystem(ecs_iter_t *it) { }

static
void BarSystem(ecs_iter_t *it) { }

void SystemMisc_add_own_component(void) {
    ecs_world_t * world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, FooSystem, 0, Position);
    ECS_SYSTEM(world, BarSystem, 0, Position);

    ecs_set(world, BarSystem, Position, {0, 0});

    /* Make sure code didn't assert */
    test_assert(true);

    ecs_fini(world);
}

static bool action_a_invoked;
static bool action_b_invoked;

static
void ActionA(ecs_iter_t *it) {
    action_a_invoked = true;
}

static
void ActionB(ecs_iter_t *it) {
    action_b_invoked = true;
}

void SystemMisc_change_system_action(void) {
    ecs_world_t * world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    
    ecs_entity_t sys = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "Sys", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "Position",
        .callback = ActionA
    });

    ecs_new_w(world, Position);

    test_bool(action_a_invoked, false);
    test_bool(action_b_invoked, false);

    ecs_progress(world, 0);

    test_bool(action_a_invoked, true);
    test_bool(action_b_invoked, false);

    action_a_invoked = false;

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = sys,
        .callback = ActionB
    });

    ecs_progress(world, 0);

    test_bool(action_a_invoked, false);
    test_bool(action_b_invoked, true);

    ecs_fini(world);
}

void SystemMisc_system_readeactivate(void) {
    ecs_world_t * world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    
    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position);

    /* No entities, system should be deactivated */
    test_assert( ecs_has_id(world, Dummy, EcsEmpty));

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_run_aperiodic(world, 0);

    /* System should be active, one entity is matched */
    test_assert( !ecs_has_id(world, Dummy, EcsEmpty));

    ecs_delete(world, e);
    ecs_run_aperiodic(world, 0);

    /* System is not automatically deactivated */
    test_assert( !ecs_has_id(world, Dummy, EcsEmpty));

    /* Manually deactivate system that aren't matched with entities */
    ecs_run_aperiodic(world, EcsAperiodicEmptyQueries);

    /* System should be deactivated */
    test_assert( ecs_has_id(world, Dummy, EcsEmpty));

    ecs_fini(world);
}

static
void Dummy1(ecs_iter_t *it) { }

static
void Dummy2(ecs_iter_t *it) { }

void SystemMisc_system_readeactivate_w_2_systems(void) {
    ecs_world_t * world = ecs_init();
    
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Mass);
    
    ECS_SYSTEM(world, Dummy1, EcsOnUpdate, Position);
    ECS_SYSTEM(world, Dummy2, EcsOnUpdate, Mass);

    /* No entities, system should be deactivated */
    test_assert( ecs_has_id(world, Dummy1, EcsEmpty));
    test_assert( ecs_has_id(world, Dummy2, EcsEmpty));

    ecs_entity_t e1 = ecs_new_w(world, Position);
    ecs_new_w(world, Mass);
    ecs_run_aperiodic(world, 0);

    /* Systems should be active, one entity is matched */
    test_assert( !ecs_has_id(world, Dummy1, EcsEmpty));
    test_assert( !ecs_has_id(world, Dummy2, EcsEmpty));

    ecs_delete(world, e1);
    ecs_run_aperiodic(world, 0);

    /* System is not automatically deactivated */
    test_assert( !ecs_has_id(world, Dummy1, EcsEmpty));
    test_assert( !ecs_has_id(world, Dummy2, EcsEmpty));

    /* Manually deactivate system that aren't matched with entities */
    ecs_run_aperiodic(world, EcsAperiodicEmptyQueries);

    /* System should be deactivated */
    test_assert( ecs_has_id(world, Dummy1, EcsEmpty));
    test_assert( !ecs_has_id(world, Dummy2, EcsEmpty));

    ecs_fini(world);
}

void SystemMisc_add_to_system_in_progress(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tag);

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position);

    ecs_new_w(world, Position);

    ecs_defer_begin(world);

    ecs_add(world, Dummy, Tag);

    ecs_defer_end(world);

    ecs_progress(world, 0);
    test_assert(dummy_invoked == true);

    ecs_fini(world);
}

static
void Action(ecs_iter_t *it) { }

void SystemMisc_redefine_null_signature(void) {
    ecs_world_t *world = ecs_init();

    ecs_entity_t s_1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "System", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = NULL,
        .callback = Action
    });

    ecs_entity_t s_2 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "System", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = NULL,
        .callback = Action
    });      

    test_assert(s_1 == s_2);

    ecs_fini(world);
}

void SystemMisc_redefine_0_signature(void) {
    ecs_world_t *world = ecs_init();

    ecs_entity_t s_1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "System", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "0",
        .callback = Action
    });

    ecs_entity_t s_2 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, { .name = "System", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "0",
        .callback = Action
    }); 

    test_assert(s_1 == s_2);

    ecs_fini(world);
}

void SystemMisc_redeclare_system_explicit_id(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t s1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}), 
        .query.expr = "Position, Velocity", 
        .callback = Dummy
    });

    ecs_entity_t s2 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = s1, .name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "Position, Velocity", 
        .callback = Dummy
    });

    test_assert(s1 == s2);

    ecs_fini(world);
}

void SystemMisc_redeclare_system_explicit_id_null_expr(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t s1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}), 
        .query.expr = NULL, 
        .callback = Dummy
    });

    ecs_entity_t s2 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = s1, .name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = NULL, 
        .callback = Dummy
    });

    test_assert(s1 == s2);

    ecs_fini(world);
}

void SystemMisc_redeclare_system_explicit_id_no_name(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t s1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}), 
        .query.expr = "Position, Velocity", 
        .callback = Dummy
    });

    ecs_entity_t s2 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = s1, .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "Position, Velocity", 
        .callback = Dummy
    });

    test_assert(s1 == s2);
    test_str(ecs_get_name(world, s1), "Move");

    ecs_fini(world);
}

void SystemMisc_declare_different_id_same_name(void) {
    install_test_abort();

    ecs_world_t *world = ecs_init();

    ecs_entity_t e1 = ecs_new(world);
    ecs_entity_t e2 = ecs_new(world);

    ecs_entity_t s_1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = e1, .name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "0", 
        .callback = Dummy
    });
    test_assert(e1 == s_1);

    test_expect_abort();

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = e2, .name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "0", 
        .callback = Dummy
    });
}

void SystemMisc_declare_different_id_same_name_w_scope(void) {
    install_test_abort();
    
    ecs_world_t *world = ecs_init();

    ecs_entity_t scope = ecs_new(world);
    ecs_set_scope(world, scope);

    ecs_entity_t e1 = ecs_new(world);
    ecs_entity_t e2 = ecs_new(world);

    ecs_entity_t s_1 = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = e1, .name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "0", 
        .callback = Dummy
    });
    test_assert(e1 == s_1);

    test_expect_abort();

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.id = e2, .name = "Move", .add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.expr = "0", 
        .callback = Dummy
    });
}

void SystemMisc_rw_in_implicit_any(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, Velocity(self|up)" });

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == false);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_in_implicit_shared(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_pair(world, ecs_id(Velocity), EcsOnInstantiate, EcsInherit);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, Velocity(up IsA)" });

    ecs_entity_t base = ecs_new_w(world, Velocity);
    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add_pair(world, e, EcsIsA, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == true);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_in_implicit_from_empty(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, Velocity()" });

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == true);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_in_implicit_from_entity(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, f, Velocity);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, Velocity(f)" });

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == true);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_out_explicit_any(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_pair(world, ecs_id(Velocity), EcsOnInstantiate, EcsInherit);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, [out] Velocity(self|up IsA)" });

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == false);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_out_explicit_shared(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_pair(world, ecs_id(Velocity), EcsOnInstantiate, EcsInherit);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, [out] Velocity(up IsA)" });

    ecs_entity_t base = ecs_new_w(world, Velocity);
    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add_pair(world, e, EcsIsA, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == false);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_out_explicit_from_empty(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, [out] Velocity()" });

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == false);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_rw_out_explicit_from_entity(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, f, Velocity);

    ecs_query_t *q = ecs_query(world, { .expr = "Position, [out] Velocity(f)" });

    ecs_entity_t e = ecs_new_w(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it) == true);
    test_assert(ecs_field_is_readonly(&it, 0) == false);
    test_assert(ecs_field_is_readonly(&it, 1) == false);
    test_assert(ecs_query_next(&it) == false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_activate_system_for_table_w_n_pairs(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Pair);
    ECS_SYSTEM(world, Dummy, EcsOnUpdate, (Pair, *));

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_set_ctx(world, &ctx, NULL);    

    ECS_ENTITY(world, e, (Pair, TagA), (Pair, TagB));
    test_assert(e != 0);

    ecs_progress(world, 0);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 2);

    test_int(ctx.e[0], e);
    test_int(ctx.e[1], e);

    test_int(ctx.c[0][0], ecs_pair(Pair, TagA));
    test_int(ctx.s[0][0], 0);
    test_int(ctx.c[1][0], ecs_pair(Pair, TagB));
    test_int(ctx.s[1][0], 0);    

    ecs_fini(world);
}

void SystemMisc_get_query(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Position);

    ecs_insert(world, ecs_value(Position, {0, 0}));
    ecs_insert(world, ecs_value(Position, {1, 0}));
    ecs_insert(world, ecs_value(Position, {2, 0}));

    ecs_query_t *q = ecs_system_get(world, Dummy)->query;
    test_assert(q != NULL);

    int32_t count = 0;

    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        Position *p = ecs_field(&it, Position, 0);
        test_assert(p != NULL);

        int i;
        for (i = 0; i < it.count; i ++) {
            test_int(p[i].x, i);
            count ++;
        }
    }

    test_int(count, 3);

    ecs_query_fini(q);

    ecs_fini(world);
}

void SystemMisc_set_get_context(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    int32_t ctx_a, ctx_b;

    ecs_entity_t s = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.name = "MySystem"}),
        .query.terms = {{Tag}},
        .callback = Dummy,
        .ctx = &ctx_a
    });
    test_assert(s != 0);

    test_assert(ecs_system_get(world, s)->ctx == &ctx_a);

    test_assert(ecs_system_init(world, &(ecs_system_desc_t){
        .entity = s,
        .ctx = &ctx_b
    }) == s);

    test_assert(ecs_system_get(world, s)->ctx == &ctx_b);

    ecs_fini(world);
}

void SystemMisc_set_get_binding_context(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    int32_t ctx_a, ctx_b;

    ecs_entity_t s = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.name = "MySystem"}),
        .query.terms = {{Tag}},
        .callback = Dummy,
        .callback_ctx = &ctx_a
    });
    test_assert(s != 0);

    test_assert(ecs_system_get(world, s)->callback_ctx == &ctx_a);

    test_assert(ecs_system_init(world, &(ecs_system_desc_t){
        .entity = s,
        .callback_ctx = &ctx_b
    }) == s);

    test_assert(ecs_system_get(world, s)->callback_ctx == &ctx_b);

    ecs_fini(world);
}

void SystemMisc_deactivate_after_disable(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ECS_SYSTEM(world, Dummy, EcsOnUpdate, Tag);

    ecs_entity_t e = ecs_new_w_id(world, Tag);
    ecs_run_aperiodic(world, 0);
    
    test_assert(!ecs_has_id(world, Dummy, EcsEmpty));

    ecs_enable(world, Dummy, false);
    test_assert(!ecs_has_id(world, Dummy, EcsEmpty));
    test_assert(ecs_has_id(world, Dummy, EcsDisabled));

    ecs_delete(world, e);
    ecs_run_aperiodic(world, 0);

    test_assert(!ecs_has_id(world, Dummy, EcsEmpty));
    test_assert(ecs_has_id(world, Dummy, EcsDisabled));

    ecs_fini(world);
}

void SystemMisc_delete_system(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.name = "Foo"}),
        .query.terms = {{.id = Tag}},
        .callback = Dummy
    });
    test_assert(system != 0);

    ecs_set_ctx(world, &ctx, NULL);

    ecs_entity_t e = ecs_new(world);
    ecs_add_id(world, e, Tag);

    ecs_run(world, system, 0, NULL);
    test_int(ctx.count, 1);
    test_assert(ctx.system == system);

    ecs_delete(world, system);
    test_assert(!ecs_is_alive(world, system));

    ecs_fini(world);
}

void SystemMisc_delete_pipeline_system(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    Probe ctx = {0};

    // Create system before
    test_assert(ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.terms = {{.id = Tag}},
        .callback = Dummy
    }) != 0);

    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.terms = {{.id = Tag}},
        .callback = Dummy
    });
    test_assert(system != 0);

    // Create system after
    test_assert(ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.terms = {{.id = Tag}},
        .callback = Dummy
    }) != 0);

    ecs_set_ctx(world, &ctx, NULL);

    ecs_entity_t e = ecs_new(world);
    ecs_add_id(world, e, Tag);

    ecs_progress(world, 0);
    test_int(ctx.count, 3);

    ctx.count = 0;

    ecs_delete(world, system);

    ecs_progress(world, 0);
    test_int(ctx.count, 2);

    ecs_fini(world);
}

static int ctx_value;
static
void ctx_free(void *ctx) {
    test_assert(&ctx_value == ctx);
    ctx_value ++;
}

static int binding_ctx_value;
static
void callback_ctx_free(void *ctx) {
    test_assert(&binding_ctx_value == ctx);
    binding_ctx_value ++;
}

static int ctx_value_2;
static
void ctx_free_2(void *ctx) {
    test_assert(&ctx_value_2 == ctx);
    ctx_value_2 ++;
}

static int binding_ctx_value_2;
static
void binding_ctx_free_2(void *ctx) {
    test_assert(&binding_ctx_value_2 == ctx);
    binding_ctx_value_2 ++;
}

void SystemMisc_delete_system_w_ctx(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .query.terms = {{.id = Tag}},
        .callback = Dummy,
        .ctx = &ctx_value,
        .ctx_free = ctx_free,
        .callback_ctx = &binding_ctx_value,
        .callback_ctx_free = callback_ctx_free
    });
    test_assert(system != 0);

    test_assert(ecs_system_get(world, system)->ctx == &ctx_value);
    test_assert(ecs_system_get(world, system)->callback_ctx 
        == &binding_ctx_value);

    ecs_set_ctx(world, &ctx, NULL);

    ecs_entity_t e = ecs_new(world);
    ecs_add_id(world, e, Tag);

    ecs_run(world, system, 0, NULL);
    test_int(ctx.count, 1);
    test_assert(ctx.system == system);

    ecs_delete(world, system);
    test_assert(!ecs_is_alive(world, system));

    ecs_fini(world);
}

void SystemMisc_update_ctx(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .query.terms = {{.id = Tag}},
        .callback = Dummy,
        .ctx = &ctx_value,
        .ctx_free = ctx_free,
        .callback_ctx = &binding_ctx_value,
        .callback_ctx_free = callback_ctx_free
    });
    test_assert(system != 0);

    test_assert(ecs_system_get(world, system)->ctx == &ctx_value);
    test_assert(ecs_system_get(world, system)->callback_ctx 
        == &binding_ctx_value);

    ecs_system(world, {
        .entity = system,
        .ctx = &ctx_value,
        .ctx_free = ctx_free,
        .callback_ctx = &binding_ctx_value,
        .callback_ctx_free = callback_ctx_free
    });

    test_int(ctx_value, 0);
    test_int(binding_ctx_value, 0);
    test_int(ctx_value_2, 0);
    test_int(binding_ctx_value_2, 0);

    ecs_system(world, {
        .entity = system,
        .ctx = &ctx_value_2,
        .ctx_free = ctx_free_2,
        .callback_ctx = &binding_ctx_value_2,
        .callback_ctx_free = binding_ctx_free_2
    });

    test_int(ctx_value, 1);
    test_int(binding_ctx_value, 1);
    test_int(ctx_value_2, 0);
    test_int(binding_ctx_value_2, 0);

    ecs_delete(world, system);

    test_int(ctx_value, 1);
    test_int(binding_ctx_value, 1);
    test_int(ctx_value_2, 1);
    test_int(binding_ctx_value_2, 1);

    ecs_fini(world);
}

static int run_invoked = 0;

static void Run(ecs_iter_t *it) {
    while (ecs_iter_next(it)) {
        probe_iter(it);
    }

    run_invoked ++;
}

static int run_2_invoked = 0;

static void Run2(ecs_iter_t *it) {
    run_2_invoked ++;
    ecs_iter_fini(it);
}

static void Run_call_callback(ecs_iter_t *it) {
    run_invoked ++;
    
    test_assert(it != NULL);
    test_assert(it->next != NULL);
    test_assert(it->callback != NULL);

    while (ecs_iter_next(it)) {
        it->callback(it);
    }
}

void SystemMisc_run_custom_run_action(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .query.terms = {{ .id = TagA }},
        .run = Run,
        .callback = Dummy,
        .ctx = &ctx,
    });
    test_assert(system != 0);

    ecs_entity_t e1 = ecs_new_w(world, TagA);
    ecs_entity_t e2 = ecs_new_w(world, TagA);
    ecs_entity_t e3 = ecs_new_w(world, TagA);
    ecs_add(world, e3, TagB); // 2 tables

    ecs_run(world, system, 0, NULL);

    test_bool(dummy_invoked, false);
    test_int(run_invoked, 1);

    test_int(ctx.invoked, 2);
    test_int(ctx.count, 3);
    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    ecs_fini(world);
}

void SystemMisc_pipeline_custom_run_action(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world, {.add = ecs_ids(ecs_dependson(EcsOnUpdate))}),
        .query.terms = {{ .id = TagA }},
        .run = Run,
        .callback = Dummy,
        .ctx = &ctx
    });
    test_assert(system != 0);

    ecs_entity_t e1 = ecs_new_w(world, TagA);
    ecs_entity_t e2 = ecs_new_w(world, TagA);
    ecs_entity_t e3 = ecs_new_w(world, TagA);
    ecs_add(world, e3, TagB); // 2 tables

    ecs_progress(world, 0);

    test_bool(dummy_invoked, false);
    test_int(run_invoked, 1);

    test_int(ctx.invoked, 2);
    test_int(ctx.count, 3);
    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    ecs_fini(world);
}

void SystemMisc_change_custom_run_action(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .query.terms = {{ .id = TagA }},
        .run = Run,
        .callback = Dummy,
        .ctx = &ctx,
    });
    test_assert(system != 0);

    ecs_new_w(world, TagA);

    ecs_run(world, system, 0, NULL);
    test_bool(dummy_invoked, false);
    test_int(run_invoked, 1);
    test_int(run_2_invoked, 0);

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = system,
        .run = Run2
    });

    ecs_run(world, system, 0, NULL);
    test_bool(dummy_invoked, false);
    test_int(run_invoked, 1);
    test_int(run_2_invoked, 1);

    ecs_fini(world);
}

void SystemMisc_custom_run_action_call_next(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system_init(world, &(ecs_system_desc_t){
        .query.terms = {{ .id = TagA }},
        .run = Run_call_callback,
        .callback = Dummy,
        .ctx = &ctx,
        .entity = ecs_entity(world, {.add = ecs_ids(ecs_dependson(EcsOnUpdate))})
    });
    test_assert(system != 0);

    ecs_entity_t e1 = ecs_new_w(world, TagA);
    ecs_entity_t e2 = ecs_new_w(world, TagA);
    ecs_entity_t e3 = ecs_new_w(world, TagA);
    ecs_add(world, e3, TagB); // 2 tables

    ecs_progress(world, 0);

    test_bool(dummy_invoked, true);
    test_int(run_invoked, 1);

    test_int(ctx.invoked, 2);
    test_int(ctx.count, 3);
    test_int(ctx.e[0], e1);
    test_int(ctx.e[1], e2);
    test_int(ctx.e[2], e3);

    ecs_fini(world);
}

void SystemMisc_system_w_short_notation(void) {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, Tag);

    Probe ctx = {0};
    ecs_entity_t system = ecs_system(world, {
        .query.terms = {{ .id = Tag }},
        .callback = Dummy,
        .ctx = &ctx,
        .entity = ecs_entity(world, {.add = ecs_ids(ecs_dependson(EcsOnUpdate))})
    });
    test_assert(system != 0);

    ecs_entity_t e = ecs_new_w(world, Tag);

    ecs_progress(world, 0);

    test_bool(dummy_invoked, true);
    test_int(ctx.invoked, 1);
    test_int(ctx.count, 1);
    test_int(ctx.e[0], e);

    ecs_fini(world);
}

void SystemMisc_update_interval_w_system_init(void) {
    ecs_world_t *world = ecs_init();

    ecs_entity_t system = ecs_system(world, {
        .callback = Dummy,
    });
    test_assert(system != 0);
    test_int(ecs_get_interval(world, system), 0);

    ecs_system(world, {
        .entity = system,
        .interval = 1.0
    });

    test_int(ecs_get_interval(world, system), 1.0);

    ecs_fini(world);
}

void SystemMisc_update_rate_w_system_init(void) {
    ecs_world_t *world = ecs_init();

    ecs_entity_t system = ecs_system(world, {
        .callback = Dummy,
    });
    test_assert(system != 0);
    test_assert(ecs_get(world, system, EcsRateFilter) == NULL);

    ecs_system(world, {
        .entity = system,
        .rate = 2.0
    });

    const EcsRateFilter *r = ecs_get(world, system, EcsRateFilter);
    test_assert(r != NULL);
    test_int(r->rate, 2.0);

    ecs_fini(world);
}

void SystemMisc_system_w_interval_rate_stop_timer(void) {
    ecs_world_t *world = ecs_init();

    ecs_entity_t system = ecs_system(world, {
        .entity = ecs_entity(world, { .add = ecs_ids(ecs_dependson(EcsOnUpdate)) }),
        .interval = 1.0,
        .rate = 3.0,
        .callback = Dummy
    });

    for (int i = 0; i < 5; i ++) {
        ecs_progress(world, 0.5);
        test_assert(dummy_invoked == 0);
    }

    ecs_progress(world, 0.5);

    test_assert(dummy_invoked == 1);
    dummy_invoked = 0;

    ecs_stop_timer(world, system);

    for (int i = 0; i < 5; i ++) {
        ecs_progress(world, 0.5);
        test_assert(dummy_invoked == 0);
    }

    ecs_progress(world, 0.5);

    test_assert(dummy_invoked == 0);

    ecs_fini(world);
}

static
int32_t sys_a_invoked = false;

static
void SA(ecs_iter_t *it) {
    sys_a_invoked = true;
}

static
int32_t sys_b_invoked = false;

static
void SB(ecs_iter_t *it) {
    sys_b_invoked = true;
}

static
int32_t sys_c_invoked = false;

static
void SC(ecs_iter_t *it) {
    sys_c_invoked = true;
}

void SystemMisc_system_same_interval_same_tick(void) {
    ecs_world_t *world = ecs_init();

    ecs_system(world, {
        .entity = ecs_entity(world, { .add = ecs_ids(ecs_dependson(EcsOnUpdate)) }),
        .interval = 1.0,
        .callback = SA
    });

    ecs_system(world, {
        .entity = ecs_entity(world, { .add = ecs_ids(ecs_dependson(EcsOnUpdate)) }),
        .interval = 1.0,
        .callback = SB
    });

    ecs_system(world, {
        .entity = ecs_entity(world, { .add = ecs_ids(ecs_dependson(EcsOnUpdate)) }),
        .interval = 1.0,
        .callback = SC
    });

    while (!sys_a_invoked) {
        test_assert(!sys_b_invoked);
        test_assert(!sys_c_invoked);
        ecs_progress(world, 0.0001);
    }

    test_assert(sys_b_invoked);
    test_assert(sys_c_invoked);

    ecs_fini(world);
}

void SystemMisc_system_no_id_in_scope(void) {
    ecs_world_t* world = ecs_mini();
    
    ECS_TAG(world, TagA);

    ecs_entity_t parent = ecs_new(world);

    ecs_set_scope(world, parent);

    ecs_entity_t s = ecs_system(world, {
        .query.terms = {
            { .id = TagA },
        },
        .callback = SA
    });

    ecs_set_scope(world, 0);

    test_assert(ecs_has_pair(world, s, EcsChildOf, parent));

    ecs_fini(world);
}

static int callback_callback_invoked = 0;
static int callback_run_invoked = 0;

static
void callback_callback(ecs_iter_t *it) {
    callback_callback_invoked ++;
}

static
void callback_run(ecs_iter_t *it) {
    callback_run_invoked ++;
}

void SystemMisc_register_callback_after_run(void) {
    ecs_world_t* world = ecs_mini();

    ecs_entity_t s = ecs_system(world, {
        .callback = callback_callback
    });

    ecs_run(world, s, 0, 0);
    test_int(callback_callback_invoked, 1);
    test_int(callback_run_invoked, 0);

    ecs_system(world, {
        .entity = s,
        .run = callback_run
    });

    ecs_run(world, s, 0, 0);
    test_int(callback_callback_invoked, 1);
    test_int(callback_run_invoked, 1);

    ecs_fini(world);
}

void SystemMisc_register_run_after_callback(void) {
    ecs_world_t* world = ecs_mini();

    ecs_entity_t s = ecs_system(world, {
        .run = callback_run
    });

    ecs_run(world, s, 0, 0);
    test_int(callback_callback_invoked, 0);
    test_int(callback_run_invoked, 1);

    ecs_system(world, {
        .entity = s,
        .callback = callback_callback
    });

    ecs_run(world, s, 0, 0);
    test_int(callback_callback_invoked, 1);
    test_int(callback_run_invoked, 1);

    ecs_fini(world);
}

static
void ctx_free_3(void *ptr) {
    int32_t *ctx = ptr;
    ctx[0]++;
}

void SystemMisc_register_callback_after_run_ctx(void) {
    ecs_world_t* world = ecs_mini();

    int32_t callback_ctx = 0, run_ctx = 0;

    ecs_entity_t s = ecs_system(world, {
        .callback = callback_callback,
        .callback_ctx = &callback_ctx,
        .callback_ctx_free = ctx_free_3
    });

    test_int(callback_ctx, 0);

    ecs_system(world, {
        .entity = s,
        .run = callback_run,
        .run_ctx = &run_ctx,
        .run_ctx_free = ctx_free_3
    });

    test_int(callback_ctx, 1);

    ecs_fini(world);

    test_int(callback_ctx, 1);
    test_int(run_ctx, 1);
}

void SystemMisc_register_run_after_callback_ctx(void) {
    ecs_world_t* world = ecs_mini();

    int32_t callback_ctx = 0, run_ctx = 0;

    ecs_entity_t s = ecs_system(world, {
        .run = callback_run,
        .run_ctx = &run_ctx,
        .run_ctx_free = ctx_free_3
    });

    test_int(run_ctx, 0);

    ecs_system(world, {
        .entity = s,
        .callback = callback_callback,
        .callback_ctx = &callback_ctx,
        .callback_ctx_free = ctx_free_3
    });

    test_int(run_ctx, 1);

    ecs_fini(world);

    test_int(callback_ctx, 1);
    test_int(run_ctx, 1);
}